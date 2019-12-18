#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_6__ {int fp_format; int /*<<< orphan*/  algorithm; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ ChromaprintMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
#define  FINGERPRINT_BASE64 130 
#define  FINGERPRINT_COMPRESSED 129 
#define  FINGERPRINT_RAW 128 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  chromaprint_dealloc (void*) ; 
 int /*<<< orphan*/  chromaprint_encode_fingerprint (void*,int,int /*<<< orphan*/ ,void**,int*,int) ; 
 int /*<<< orphan*/  chromaprint_finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chromaprint_get_raw_fingerprint (int /*<<< orphan*/ ,void**,int*) ; 
 int /*<<< orphan*/  cleanup (TYPE_1__*) ; 

__attribute__((used)) static int write_trailer(AVFormatContext *s)
{
    ChromaprintMuxContext *cpr = s->priv_data;
    AVIOContext *pb = s->pb;
    void *fp = NULL, *enc_fp = NULL;
    int size, enc_size, ret = AVERROR(EINVAL);

    if (!chromaprint_finish(cpr->ctx)) {
        av_log(s, AV_LOG_ERROR, "Failed to generate fingerprint\n");
        goto fail;
    }

    if (!chromaprint_get_raw_fingerprint(cpr->ctx, &fp, &size)) {
        av_log(s, AV_LOG_ERROR, "Failed to retrieve fingerprint\n");
        goto fail;
    }

    switch (cpr->fp_format) {
    case FINGERPRINT_RAW:
        avio_write(pb, fp, size * 4); //fp points to array of uint32_t
        break;
    case FINGERPRINT_COMPRESSED:
    case FINGERPRINT_BASE64:
        if (!chromaprint_encode_fingerprint(fp, size, cpr->algorithm, &enc_fp, &enc_size,
                                            cpr->fp_format == FINGERPRINT_BASE64)) {
            av_log(s, AV_LOG_ERROR, "Failed to encode fingerprint\n");
            goto fail;
        }
        avio_write(pb, enc_fp, enc_size);
        break;
    }

    ret = 0;
fail:
    if (fp)
        chromaprint_dealloc(fp);
    if (enc_fp)
        chromaprint_dealloc(enc_fp);
    cleanup(cpr);
    return ret;
}