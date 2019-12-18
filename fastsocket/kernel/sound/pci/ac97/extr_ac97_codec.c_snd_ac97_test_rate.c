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
struct snd_ac97 {TYPE_1__* bus; } ;
struct TYPE_2__ {unsigned int clock; } ;

/* Variables and functions */
 unsigned short snd_ac97_read (struct snd_ac97*,int) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (struct snd_ac97*,int,unsigned int) ; 

__attribute__((used)) static int snd_ac97_test_rate(struct snd_ac97 *ac97, int reg, int shadow_reg, int rate)
{
	unsigned short val;
	unsigned int tmp;

	tmp = ((unsigned int)rate * ac97->bus->clock) / 48000;
	snd_ac97_write_cache(ac97, reg, tmp & 0xffff);
	if (shadow_reg)
		snd_ac97_write_cache(ac97, shadow_reg, tmp & 0xffff);
	val = snd_ac97_read(ac97, reg);
	return val == (tmp & 0xffff);
}