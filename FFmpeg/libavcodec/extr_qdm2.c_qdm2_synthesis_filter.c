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
struct TYPE_3__ {int sub_sampling; int channels; int nb_channels; float* samples; int frame_size; int* output_buffer; scalar_t__*** sb_samples; int /*<<< orphan*/ * synth_buf_offset; int /*<<< orphan*/ * synth_buf; int /*<<< orphan*/  mpadsp; } ;
typedef  TYPE_1__ QDM2Context ;

/* Variables and functions */
 int QDM2_SB_USED (int) ; 
 int SBLIMIT ; 
 int /*<<< orphan*/  ff_mpa_synth_filter_float (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,float*,int,scalar_t__*) ; 
 int /*<<< orphan*/  ff_mpa_synth_window_float ; 

__attribute__((used)) static void qdm2_synthesis_filter(QDM2Context *q, int index)
{
    int i, k, ch, sb_used, sub_sampling, dither_state = 0;

    /* copy sb_samples */
    sb_used = QDM2_SB_USED(q->sub_sampling);

    for (ch = 0; ch < q->channels; ch++)
        for (i = 0; i < 8; i++)
            for (k = sb_used; k < SBLIMIT; k++)
                q->sb_samples[ch][(8 * index) + i][k] = 0;

    for (ch = 0; ch < q->nb_channels; ch++) {
        float *samples_ptr = q->samples + ch;

        for (i = 0; i < 8; i++) {
            ff_mpa_synth_filter_float(&q->mpadsp,
                                      q->synth_buf[ch], &(q->synth_buf_offset[ch]),
                                      ff_mpa_synth_window_float, &dither_state,
                                      samples_ptr, q->nb_channels,
                                      q->sb_samples[ch][(8 * index) + i]);
            samples_ptr += 32 * q->nb_channels;
        }
    }

    /* add samples to output buffer */
    sub_sampling = (4 >> q->sub_sampling);

    for (ch = 0; ch < q->channels; ch++)
        for (i = 0; i < q->frame_size; i++)
            q->output_buffer[q->channels * i + ch] += (1 << 23) * q->samples[q->nb_channels * sub_sampling * i + ch];
}