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
typedef  int /*<<< orphan*/  uint8_t ;
struct SRTPContext {int rtp_hmac_size; int rtcp_hmac_size; int /*<<< orphan*/  rtcp_auth; int /*<<< orphan*/  master_salt; int /*<<< orphan*/  aes; int /*<<< orphan*/  rtcp_salt; int /*<<< orphan*/  rtcp_key; int /*<<< orphan*/  rtp_auth; int /*<<< orphan*/  rtp_salt; int /*<<< orphan*/  rtp_key; int /*<<< orphan*/  master_key; int /*<<< orphan*/  hmac; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_HMAC_SHA1 ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_aes_alloc () ; 
 int /*<<< orphan*/  av_aes_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int av_base64_decode (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  av_hmac_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  derive_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_srtp_free (struct SRTPContext*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int ff_srtp_set_crypto(struct SRTPContext *s, const char *suite,
                       const char *params)
{
    uint8_t buf[30];

    ff_srtp_free(s);

    // RFC 4568
    if (!strcmp(suite, "AES_CM_128_HMAC_SHA1_80") ||
        !strcmp(suite, "SRTP_AES128_CM_HMAC_SHA1_80")) {
        s->rtp_hmac_size = s->rtcp_hmac_size = 10;
    } else if (!strcmp(suite, "AES_CM_128_HMAC_SHA1_32")) {
        s->rtp_hmac_size = s->rtcp_hmac_size = 4;
    } else if (!strcmp(suite, "SRTP_AES128_CM_HMAC_SHA1_32")) {
        // RFC 5764 section 4.1.2
        s->rtp_hmac_size  = 4;
        s->rtcp_hmac_size = 10;
    } else {
        av_log(NULL, AV_LOG_WARNING, "SRTP Crypto suite %s not supported\n",
                                     suite);
        return AVERROR(EINVAL);
    }
    if (av_base64_decode(buf, params, sizeof(buf)) != sizeof(buf)) {
        av_log(NULL, AV_LOG_WARNING, "Incorrect amount of SRTP params\n");
        return AVERROR(EINVAL);
    }
    // MKI and lifetime not handled yet
    s->aes  = av_aes_alloc();
    s->hmac = av_hmac_alloc(AV_HMAC_SHA1);
    if (!s->aes || !s->hmac)
        return AVERROR(ENOMEM);
    memcpy(s->master_key, buf, 16);
    memcpy(s->master_salt, buf + 16, 14);

    // RFC 3711
    av_aes_init(s->aes, s->master_key, 128, 0);

    derive_key(s->aes, s->master_salt, 0x00, s->rtp_key, sizeof(s->rtp_key));
    derive_key(s->aes, s->master_salt, 0x02, s->rtp_salt, sizeof(s->rtp_salt));
    derive_key(s->aes, s->master_salt, 0x01, s->rtp_auth, sizeof(s->rtp_auth));

    derive_key(s->aes, s->master_salt, 0x03, s->rtcp_key, sizeof(s->rtcp_key));
    derive_key(s->aes, s->master_salt, 0x05, s->rtcp_salt, sizeof(s->rtcp_salt));
    derive_key(s->aes, s->master_salt, 0x04, s->rtcp_auth, sizeof(s->rtcp_auth));
    return 0;
}