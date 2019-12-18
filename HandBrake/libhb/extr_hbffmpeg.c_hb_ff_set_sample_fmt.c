#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_6__ {scalar_t__ type; int* sample_fmts; } ;
struct TYPE_5__ {int request_sample_fmt; int sample_fmt; } ;
typedef  TYPE_1__ AVCodecContext ;
typedef  TYPE_2__ AVCodec ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int const AV_SAMPLE_FMT_NONE ; 
 int av_get_packed_sample_fmt (int) ; 
 int av_get_planar_sample_fmt (int) ; 
 scalar_t__ av_sample_fmt_is_planar (int) ; 

void hb_ff_set_sample_fmt(AVCodecContext *context, AVCodec *codec,
                          enum AVSampleFormat request_sample_fmt)
{
    if (context != NULL && codec != NULL &&
        codec->type == AVMEDIA_TYPE_AUDIO && codec->sample_fmts != NULL)
    {
        const enum AVSampleFormat *fmt;
        enum AVSampleFormat next_best_fmt;

        next_best_fmt = (av_sample_fmt_is_planar(request_sample_fmt)  ?
                         av_get_packed_sample_fmt(request_sample_fmt) :
                         av_get_planar_sample_fmt(request_sample_fmt));

        context->request_sample_fmt = AV_SAMPLE_FMT_NONE;

        for (fmt = codec->sample_fmts; *fmt != AV_SAMPLE_FMT_NONE; fmt++)
        {
            if (*fmt == request_sample_fmt)
            {
                context->request_sample_fmt = request_sample_fmt;
                break;
            }
            else if (*fmt == next_best_fmt)
            {
                context->request_sample_fmt = next_best_fmt;
            }
        }

        /*
         * When encoding and AVCodec.sample_fmts exists, avcodec_open2()
         * will error out if AVCodecContext.sample_fmt isn't set.
         */
        if (context->request_sample_fmt == AV_SAMPLE_FMT_NONE)
        {
            context->request_sample_fmt = codec->sample_fmts[0];
        }
        context->sample_fmt = context->request_sample_fmt;
    }
}