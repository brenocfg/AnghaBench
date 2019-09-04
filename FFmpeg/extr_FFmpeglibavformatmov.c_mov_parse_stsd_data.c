#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int int64_t ;
struct TYPE_13__ {scalar_t__ codec_tag; char* extradata; } ;
struct TYPE_9__ {int num; int den; } ;
struct TYPE_12__ {int /*<<< orphan*/  metadata; TYPE_8__* codecpar; TYPE_1__ avg_frame_rate; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  fc; } ;
struct TYPE_10__ {int tmcd_flags; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  TYPE_3__ MOVContext ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_DICT_DONT_STRDUP_VAL ; 
 scalar_t__ AV_RB16 (char*) ; 
 int AV_RB32 (char*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_malloc (scalar_t__) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int ff_get_extradata (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 

__attribute__((used)) static int mov_parse_stsd_data(MOVContext *c, AVIOContext *pb,
                                AVStream *st, MOVStreamContext *sc,
                                int64_t size)
{
    int ret;

    if (st->codecpar->codec_tag == MKTAG('t','m','c','d')) {
        if ((int)size != size)
            return AVERROR(ENOMEM);

        ret = ff_get_extradata(c->fc, st->codecpar, pb, size);
        if (ret < 0)
            return ret;
        if (size > 16) {
            MOVStreamContext *tmcd_ctx = st->priv_data;
            int val;
            val = AV_RB32(st->codecpar->extradata + 4);
            tmcd_ctx->tmcd_flags = val;
            st->avg_frame_rate.num = st->codecpar->extradata[16]; /* number of frame */
            st->avg_frame_rate.den = 1;
#if FF_API_LAVF_AVCTX
FF_DISABLE_DEPRECATION_WARNINGS
            st->codec->time_base = av_inv_q(st->avg_frame_rate);
FF_ENABLE_DEPRECATION_WARNINGS
#endif
            /* adjust for per frame dur in counter mode */
            if (tmcd_ctx->tmcd_flags & 0x0008) {
                int timescale = AV_RB32(st->codecpar->extradata + 8);
                int framedur = AV_RB32(st->codecpar->extradata + 12);
                st->avg_frame_rate.num *= timescale;
                st->avg_frame_rate.den *= framedur;
#if FF_API_LAVF_AVCTX
FF_DISABLE_DEPRECATION_WARNINGS
                st->codec->time_base.den *= timescale;
                st->codec->time_base.num *= framedur;
FF_ENABLE_DEPRECATION_WARNINGS
#endif
            }
            if (size > 30) {
                uint32_t len = AV_RB32(st->codecpar->extradata + 18); /* name atom length */
                uint32_t format = AV_RB32(st->codecpar->extradata + 22);
                if (format == AV_RB32("name") && (int64_t)size >= (int64_t)len + 18) {
                    uint16_t str_size = AV_RB16(st->codecpar->extradata + 26); /* string length */
                    if (str_size > 0 && size >= (int)str_size + 26) {
                        char *reel_name = av_malloc(str_size + 1);
                        if (!reel_name)
                            return AVERROR(ENOMEM);
                        memcpy(reel_name, st->codecpar->extradata + 30, str_size);
                        reel_name[str_size] = 0; /* Add null terminator */
                        /* don't add reel_name if emtpy string */
                        if (*reel_name == 0) {
                            av_free(reel_name);
                        } else {
                            av_dict_set(&st->metadata, "reel_name", reel_name,  AV_DICT_DONT_STRDUP_VAL);
                        }
                    }
                }
            }
        }
    } else {
        /* other codec type, just skip (rtp, mp4s ...) */
        avio_skip(pb, size);
    }
    return 0;
}