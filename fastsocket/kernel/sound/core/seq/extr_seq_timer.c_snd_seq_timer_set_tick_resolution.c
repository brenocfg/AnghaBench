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
struct snd_seq_timer_tick {int resolution; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_seq_timer_update_tick (struct snd_seq_timer_tick*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_seq_timer_set_tick_resolution(struct snd_seq_timer_tick *tick,
					      int tempo, int ppq)
{
	if (tempo < 1000000)
		tick->resolution = (tempo * 1000) / ppq;
	else {
		/* might overflow.. */
		unsigned int s;
		s = tempo % ppq;
		s = (s * 1000) / ppq;
		tick->resolution = (tempo / ppq) * 1000;
		tick->resolution += s;
	}
	if (tick->resolution <= 0)
		tick->resolution = 1;
	snd_seq_timer_update_tick(tick, 0);
}