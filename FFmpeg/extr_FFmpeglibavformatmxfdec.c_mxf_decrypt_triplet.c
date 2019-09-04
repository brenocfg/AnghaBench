#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int int64_t ;
struct TYPE_18__ {int keylen; scalar_t__ key; int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_17__ {int* data; int stream_index; } ;
struct TYPE_16__ {int length; int* key; int /*<<< orphan*/  offset; } ;
struct TYPE_15__ {scalar_t__ aesc; } ;
typedef  TYPE_1__ MXFContext ;
typedef  TYPE_2__ KLVPacket ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  IS_KLV_KEY (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ av_aes_alloc () ; 
 int /*<<< orphan*/  av_aes_crypt (scalar_t__,int*,int*,int,int*,int) ; 
 int /*<<< orphan*/  av_aes_init (scalar_t__,scalar_t__,int,int) ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_shrink_packet (TYPE_3__*,int) ; 
 int avio_rb64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int find_body_sid_by_absolute_offset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int klv_decode_ber_length (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int*,int const*,int) ; 
 int /*<<< orphan*/  mxf_essence_element_key ; 
 int mxf_get_stream_index (TYPE_4__*,TYPE_2__*,int) ; 

__attribute__((used)) static int mxf_decrypt_triplet(AVFormatContext *s, AVPacket *pkt, KLVPacket *klv)
{
    static const uint8_t checkv[16] = {0x43, 0x48, 0x55, 0x4b, 0x43, 0x48, 0x55, 0x4b, 0x43, 0x48, 0x55, 0x4b, 0x43, 0x48, 0x55, 0x4b};
    MXFContext *mxf = s->priv_data;
    AVIOContext *pb = s->pb;
    int64_t end = avio_tell(pb) + klv->length;
    int64_t size;
    uint64_t orig_size;
    uint64_t plaintext_size;
    uint8_t ivec[16];
    uint8_t tmpbuf[16];
    int index;
    int body_sid;

    if (!mxf->aesc && s->key && s->keylen == 16) {
        mxf->aesc = av_aes_alloc();
        if (!mxf->aesc)
            return AVERROR(ENOMEM);
        av_aes_init(mxf->aesc, s->key, 128, 1);
    }
    // crypto context
    size = klv_decode_ber_length(pb);
    if (size < 0)
        return size;
    avio_skip(pb, size);
    // plaintext offset
    klv_decode_ber_length(pb);
    plaintext_size = avio_rb64(pb);
    // source klv key
    klv_decode_ber_length(pb);
    avio_read(pb, klv->key, 16);
    if (!IS_KLV_KEY(klv, mxf_essence_element_key))
        return AVERROR_INVALIDDATA;

    body_sid = find_body_sid_by_absolute_offset(mxf, klv->offset);
    index = mxf_get_stream_index(s, klv, body_sid);
    if (index < 0)
        return AVERROR_INVALIDDATA;
    // source size
    klv_decode_ber_length(pb);
    orig_size = avio_rb64(pb);
    if (orig_size < plaintext_size)
        return AVERROR_INVALIDDATA;
    // enc. code
    size = klv_decode_ber_length(pb);
    if (size < 32 || size - 32 < orig_size)
        return AVERROR_INVALIDDATA;
    avio_read(pb, ivec, 16);
    avio_read(pb, tmpbuf, 16);
    if (mxf->aesc)
        av_aes_crypt(mxf->aesc, tmpbuf, tmpbuf, 1, ivec, 1);
    if (memcmp(tmpbuf, checkv, 16))
        av_log(s, AV_LOG_ERROR, "probably incorrect decryption key\n");
    size -= 32;
    size = av_get_packet(pb, pkt, size);
    if (size < 0)
        return size;
    else if (size < plaintext_size)
        return AVERROR_INVALIDDATA;
    size -= plaintext_size;
    if (mxf->aesc)
        av_aes_crypt(mxf->aesc, &pkt->data[plaintext_size],
                     &pkt->data[plaintext_size], size >> 4, ivec, 1);
    av_shrink_packet(pkt, orig_size);
    pkt->stream_index = index;
    avio_skip(pb, end - avio_tell(pb));
    return 0;
}