#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_tea575x {int freq; unsigned long val; TYPE_1__* ops; scalar_t__ freq_fixup; scalar_t__ tea5759; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct snd_tea575x*,unsigned long) ;} ;

/* Variables and functions */
 unsigned long TEA575X_BIT_FREQ_MASK ; 
 int /*<<< orphan*/  stub1 (struct snd_tea575x*,unsigned long) ; 

__attribute__((used)) static void snd_tea575x_set_freq(struct snd_tea575x *tea)
{
	unsigned long freq;

	freq = tea->freq / 16;		/* to kHz */
	if (freq > 108000)
		freq = 108000;
	if (freq < 87000)
		freq = 87000;
	/* crystal fixup */
	if (tea->tea5759)
		freq -= tea->freq_fixup;
	else
		freq += tea->freq_fixup;
	/* freq /= 12.5 */
	freq *= 10;
	freq /= 125;

	tea->val &= ~TEA575X_BIT_FREQ_MASK;
	tea->val |= freq & TEA575X_BIT_FREQ_MASK;
	tea->ops->write(tea, tea->val);
}