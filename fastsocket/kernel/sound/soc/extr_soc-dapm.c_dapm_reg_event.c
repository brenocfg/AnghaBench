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
struct snd_soc_dapm_widget {unsigned int on_val; unsigned int off_val; int reg; int mask; int shift; int /*<<< orphan*/  codec; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  snd_soc_update_bits (int /*<<< orphan*/ ,int,int,unsigned int) ; 

int dapm_reg_event(struct snd_soc_dapm_widget *w,
		   struct snd_kcontrol *kcontrol, int event)
{
	unsigned int val;

	if (SND_SOC_DAPM_EVENT_ON(event))
		val = w->on_val;
	else
		val = w->off_val;

	snd_soc_update_bits(w->codec, -(w->reg + 1),
			    w->mask << w->shift, val << w->shift);

	return 0;
}