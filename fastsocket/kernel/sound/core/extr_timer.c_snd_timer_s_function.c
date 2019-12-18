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
struct snd_timer_system_private {long correction; scalar_t__ last_jiffies; scalar_t__ last_expires; } ;
struct snd_timer {struct snd_timer_system_private* private_data; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 int /*<<< orphan*/  snd_timer_interrupt (struct snd_timer*,long) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static void snd_timer_s_function(unsigned long data)
{
	struct snd_timer *timer = (struct snd_timer *)data;
	struct snd_timer_system_private *priv = timer->private_data;
	unsigned long jiff = jiffies;
	if (time_after(jiff, priv->last_expires))
		priv->correction += (long)jiff - (long)priv->last_expires;
	snd_timer_interrupt(timer, (long)jiff - (long)priv->last_jiffies);
}