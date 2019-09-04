#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct SRTPContext {int rtcp_hmac_size; int rtp_hmac_size; int seq_largest; int roc; int /*<<< orphan*/  hmac; int /*<<< orphan*/  rtp_auth; int /*<<< orphan*/  rtcp_auth; int /*<<< orphan*/  aes; int /*<<< orphan*/  rtp_key; int /*<<< orphan*/  rtcp_key; int /*<<< orphan*/  rtp_salt; int /*<<< orphan*/  rtcp_salt; int /*<<< orphan*/  rtcp_index; } ;
typedef  int /*<<< orphan*/  hmac ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_RB16 (int*) ; 
 int /*<<< orphan*/  AV_RB32 (int*) ; 
 int /*<<< orphan*/  AV_WB32 (int*,int) ; 
 int RTP_PT_IS_RTCP (int const) ; 
 int /*<<< orphan*/  av_aes_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_hmac_final (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  av_hmac_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_hmac_update (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  create_iv (int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encrypt_counter (int /*<<< orphan*/ ,int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

int ff_srtp_encrypt(struct SRTPContext *s, const uint8_t *in, int len,
                    uint8_t *out, int outlen)
{
    uint8_t iv[16] = { 0 }, hmac[20];
    uint64_t index;
    uint32_t ssrc;
    int rtcp, hmac_size, padding;
    uint8_t *buf;

    if (len < 8)
        return AVERROR_INVALIDDATA;

    rtcp = RTP_PT_IS_RTCP(in[1]);
    hmac_size = rtcp ? s->rtcp_hmac_size : s->rtp_hmac_size;
    padding = hmac_size;
    if (rtcp)
        padding += 4; // For the RTCP index

    if (len + padding > outlen)
        return 0;

    memcpy(out, in, len);
    buf = out;

    if (rtcp) {
        ssrc = AV_RB32(buf + 4);
        index = s->rtcp_index++;

        buf += 8;
        len -= 8;
    } else {
        int ext, csrc;
        int seq = AV_RB16(buf + 2);

        if (len < 12)
            return AVERROR_INVALIDDATA;

        ssrc = AV_RB32(buf + 8);

        if (seq < s->seq_largest)
            s->roc++;
        s->seq_largest = seq;
        index = seq + (((uint64_t)s->roc) << 16);

        csrc = buf[0] & 0x0f;
        ext = buf[0] & 0x10;

        buf += 12;
        len -= 12;

        buf += 4 * csrc;
        len -= 4 * csrc;
        if (len < 0)
            return AVERROR_INVALIDDATA;

        if (ext) {
            if (len < 4)
                return AVERROR_INVALIDDATA;
            ext = (AV_RB16(buf + 2) + 1) * 4;
            if (len < ext)
                return AVERROR_INVALIDDATA;
            len -= ext;
            buf += ext;
        }
    }

    create_iv(iv, rtcp ? s->rtcp_salt : s->rtp_salt, index, ssrc);
    av_aes_init(s->aes, rtcp ? s->rtcp_key : s->rtp_key, 128, 0);
    encrypt_counter(s->aes, iv, buf, len);

    if (rtcp) {
        AV_WB32(buf + len, 0x80000000 | index);
        len += 4;
    }

    av_hmac_init(s->hmac, rtcp ? s->rtcp_auth : s->rtp_auth, sizeof(s->rtp_auth));
    av_hmac_update(s->hmac, out, buf + len - out);
    if (!rtcp) {
        uint8_t rocbuf[4];
        AV_WB32(rocbuf, s->roc);
        av_hmac_update(s->hmac, rocbuf, 4);
    }
    av_hmac_final(s->hmac, hmac, sizeof(hmac));

    memcpy(buf + len, hmac, hmac_size);
    len += hmac_size;
    return buf + len - out;
}