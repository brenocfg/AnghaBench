#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct audio {int rx_iir_enable; scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  audio_dsp_set_rx_iir (struct audio*) ; 

__attribute__((used)) static int audio_enable_rx_iir(struct audio *audio, int enable)
{
	if (audio->rx_iir_enable != enable) {
		audio->rx_iir_enable = enable;
		if (audio->running)
			audio_dsp_set_rx_iir(audio);
	}
	return 0;
}