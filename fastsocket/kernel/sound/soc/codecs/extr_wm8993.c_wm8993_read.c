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
typedef  unsigned int u16 ;
struct snd_soc_codec {unsigned int* reg_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int WM8993_MAX_REGISTER ; 
 unsigned int wm8993_read_hw (struct snd_soc_codec*,unsigned int) ; 
 scalar_t__ wm8993_volatile (unsigned int) ; 

__attribute__((used)) static unsigned int wm8993_read(struct snd_soc_codec *codec,
				unsigned int reg)
{
	u16 *reg_cache = codec->reg_cache;

	BUG_ON(reg > WM8993_MAX_REGISTER);

	if (wm8993_volatile(reg))
		return wm8993_read_hw(codec, reg);
	else
		return reg_cache[reg];
}