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
struct TYPE_3__ {scalar_t__ use_channel_map; int /*<<< orphan*/  mix_matrix; int /*<<< orphan*/  am; int /*<<< orphan*/  resample; int /*<<< orphan*/  ac_out; int /*<<< orphan*/  ac_in; int /*<<< orphan*/ * out_fifo; int /*<<< orphan*/  out_buffer; int /*<<< orphan*/  resample_out_buffer; int /*<<< orphan*/  in_buffer; } ;
typedef  TYPE_1__ AVAudioResampleContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_audio_fifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_audio_convert_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_audio_data_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_audio_mix_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_audio_resample_free (int /*<<< orphan*/ *) ; 

void avresample_close(AVAudioResampleContext *avr)
{
    ff_audio_data_free(&avr->in_buffer);
    ff_audio_data_free(&avr->resample_out_buffer);
    ff_audio_data_free(&avr->out_buffer);
    av_audio_fifo_free(avr->out_fifo);
    avr->out_fifo = NULL;
    ff_audio_convert_free(&avr->ac_in);
    ff_audio_convert_free(&avr->ac_out);
    ff_audio_resample_free(&avr->resample);
    ff_audio_mix_free(&avr->am);
    av_freep(&avr->mix_matrix);

    avr->use_channel_map = 0;
}