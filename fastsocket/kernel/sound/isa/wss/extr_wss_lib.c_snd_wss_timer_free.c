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
struct snd_wss {int /*<<< orphan*/ * timer; } ;
struct snd_timer {struct snd_wss* private_data; } ;

/* Variables and functions */

__attribute__((used)) static void snd_wss_timer_free(struct snd_timer *timer)
{
	struct snd_wss *chip = timer->private_data;
	chip->timer = NULL;
}