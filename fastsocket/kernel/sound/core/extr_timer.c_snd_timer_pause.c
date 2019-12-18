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
struct snd_timer_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_TIMER_EVENT_PAUSE ; 
 int _snd_timer_stop (struct snd_timer_instance*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_timer_pause(struct snd_timer_instance * timeri)
{
	return _snd_timer_stop(timeri, 0, SNDRV_TIMER_EVENT_PAUSE);
}