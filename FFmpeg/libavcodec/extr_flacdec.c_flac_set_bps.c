#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_6__ {int bps; } ;
struct TYPE_7__ {int sample_shift; TYPE_2__ flac_stream_info; TYPE_1__* avctx; } ;
struct TYPE_5__ {int request_sample_fmt; int /*<<< orphan*/  sample_fmt; } ;
typedef  TYPE_3__ FLACContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16 ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16P ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S32 ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S32P ; 
 int av_get_bytes_per_sample (int) ; 
 int av_sample_fmt_is_planar (int) ; 

__attribute__((used)) static void flac_set_bps(FLACContext *s)
{
    enum AVSampleFormat req = s->avctx->request_sample_fmt;
    int need32 = s->flac_stream_info.bps > 16;
    int want32 = av_get_bytes_per_sample(req) > 2;
    int planar = av_sample_fmt_is_planar(req);

    if (need32 || want32) {
        if (planar)
            s->avctx->sample_fmt = AV_SAMPLE_FMT_S32P;
        else
            s->avctx->sample_fmt = AV_SAMPLE_FMT_S32;
        s->sample_shift = 32 - s->flac_stream_info.bps;
    } else {
        if (planar)
            s->avctx->sample_fmt = AV_SAMPLE_FMT_S16P;
        else
            s->avctx->sample_fmt = AV_SAMPLE_FMT_S16;
        s->sample_shift = 16 - s->flac_stream_info.bps;
    }
}