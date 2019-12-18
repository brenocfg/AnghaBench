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
struct TYPE_3__ {int nb_buffers; scalar_t__ nb_samples; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ AVAudioFifo ;

/* Variables and functions */
 int /*<<< orphan*/  av_fifo_reset (int /*<<< orphan*/ ) ; 

void av_audio_fifo_reset(AVAudioFifo *af)
{
    int i;

    for (i = 0; i < af->nb_buffers; i++)
        av_fifo_reset(af->buf[i]);

    af->nb_samples = 0;
}