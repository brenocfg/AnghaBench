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
struct TYPE_7__ {int nb_samples; scalar_t__* extended_data; } ;
struct TYPE_6__ {int channels; double target_rms; double peak_value; int /*<<< orphan*/  delay; scalar_t__* dc_correction_value; scalar_t__ dc_correction; scalar_t__ alt_boundary_mode; int /*<<< orphan*/  frame_len; } ;
typedef  TYPE_1__ DynamicAudioNormalizerContext ;
typedef  TYPE_2__ AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 double DBL_EPSILON ; 
 int /*<<< orphan*/  ENOMEM ; 
 double FFMIN (double,double) ; 
 TYPE_2__* ff_get_audio_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int filter_frame (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int flush_buffer(DynamicAudioNormalizerContext *s, AVFilterLink *inlink,
                        AVFilterLink *outlink)
{
    AVFrame *out = ff_get_audio_buffer(outlink, s->frame_len);
    int c, i;

    if (!out)
        return AVERROR(ENOMEM);

    for (c = 0; c < s->channels; c++) {
        double *dst_ptr = (double *)out->extended_data[c];

        for (i = 0; i < out->nb_samples; i++) {
            dst_ptr[i] = s->alt_boundary_mode ? DBL_EPSILON : ((s->target_rms > DBL_EPSILON) ? FFMIN(s->peak_value, s->target_rms) : s->peak_value);
            if (s->dc_correction) {
                dst_ptr[i] *= ((i % 2) == 1) ? -1 : 1;
                dst_ptr[i] += s->dc_correction_value[c];
            }
        }
    }

    s->delay--;
    return filter_frame(inlink, out);
}