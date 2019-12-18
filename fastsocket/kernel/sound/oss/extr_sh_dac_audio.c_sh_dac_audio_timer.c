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
struct hrtimer {int dummy; } ;
typedef  enum hrtimer_restart { ____Placeholder_hrtimer_restart } hrtimer_restart ;

/* Variables and functions */
 int BUFFER_SIZE ; 
 int /*<<< orphan*/  CONFIG_SOUND_SH_DAC_AUDIO_CHANNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int HRTIMER_NORESTART ; 
 int /*<<< orphan*/ * buffer_begin ; 
 int /*<<< orphan*/ * buffer_end ; 
 int /*<<< orphan*/ * data_buffer ; 
 int empty ; 
 int /*<<< orphan*/  hrtimer ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_dac_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeups_per_second ; 

__attribute__((used)) static enum hrtimer_restart sh_dac_audio_timer(struct hrtimer *handle)
{
	if (!empty) {
		sh_dac_output(*buffer_begin, CONFIG_SOUND_SH_DAC_AUDIO_CHANNEL);
		buffer_begin++;

		if (buffer_begin == data_buffer + BUFFER_SIZE)
			buffer_begin = data_buffer;
		if (buffer_begin == buffer_end)
			empty = 1;
	}

	if (!empty)
		hrtimer_start(&hrtimer, wakeups_per_second, HRTIMER_MODE_REL);

	return HRTIMER_NORESTART;
}