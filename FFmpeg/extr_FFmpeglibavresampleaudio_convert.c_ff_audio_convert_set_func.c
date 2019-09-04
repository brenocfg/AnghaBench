#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_3__ {int func_type; int in_fmt; int out_fmt; char const* func_descr; int ptr_align; int samples_align; char const* func_descr_generic; int has_optimized_func; int channels; int /*<<< orphan*/  avr; void* conv_deinterleave_generic; void* conv_deinterleave; void* conv_interleave_generic; void* conv_interleave; void* conv_flat_generic; void* conv_flat; } ;
typedef  TYPE_1__ AudioConvert ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
#define  CONV_FUNC_TYPE_DEINTERLEAVE 130 
#define  CONV_FUNC_TYPE_FLAT 129 
#define  CONV_FUNC_TYPE_INTERLEAVE 128 
 int av_get_packed_sample_fmt (int) ; 
 int /*<<< orphan*/  av_get_sample_fmt_name (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

void ff_audio_convert_set_func(AudioConvert *ac, enum AVSampleFormat out_fmt,
                               enum AVSampleFormat in_fmt, int channels,
                               int ptr_align, int samples_align,
                               const char *descr, void *conv)
{
    int found = 0;

    switch (ac->func_type) {
    case CONV_FUNC_TYPE_FLAT:
        if (av_get_packed_sample_fmt(ac->in_fmt)  == in_fmt &&
            av_get_packed_sample_fmt(ac->out_fmt) == out_fmt) {
            ac->conv_flat     = conv;
            ac->func_descr    = descr;
            ac->ptr_align     = ptr_align;
            ac->samples_align = samples_align;
            if (ptr_align == 1 && samples_align == 1) {
                ac->conv_flat_generic  = conv;
                ac->func_descr_generic = descr;
            } else {
                ac->has_optimized_func = 1;
            }
            found = 1;
        }
        break;
    case CONV_FUNC_TYPE_INTERLEAVE:
        if (ac->in_fmt == in_fmt && ac->out_fmt == out_fmt &&
            (!channels || ac->channels == channels)) {
            ac->conv_interleave = conv;
            ac->func_descr      = descr;
            ac->ptr_align       = ptr_align;
            ac->samples_align   = samples_align;
            if (ptr_align == 1 && samples_align == 1) {
                ac->conv_interleave_generic = conv;
                ac->func_descr_generic      = descr;
            } else {
                ac->has_optimized_func = 1;
            }
            found = 1;
        }
        break;
    case CONV_FUNC_TYPE_DEINTERLEAVE:
        if (ac->in_fmt == in_fmt && ac->out_fmt == out_fmt &&
            (!channels || ac->channels == channels)) {
            ac->conv_deinterleave = conv;
            ac->func_descr        = descr;
            ac->ptr_align         = ptr_align;
            ac->samples_align     = samples_align;
            if (ptr_align == 1 && samples_align == 1) {
                ac->conv_deinterleave_generic = conv;
                ac->func_descr_generic        = descr;
            } else {
                ac->has_optimized_func = 1;
            }
            found = 1;
        }
        break;
    }
    if (found) {
        av_log(ac->avr, AV_LOG_DEBUG, "audio_convert: found function: %-4s "
               "to %-4s (%s)\n", av_get_sample_fmt_name(ac->in_fmt),
               av_get_sample_fmt_name(ac->out_fmt), descr);
    }
}