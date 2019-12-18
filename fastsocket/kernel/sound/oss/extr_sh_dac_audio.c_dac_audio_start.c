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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_SOUND_SH_DAC_AUDIO_CHANNEL ; 
 int /*<<< orphan*/  HD64461_GPADR ; 
 int /*<<< orphan*/  HD64461_GPADR_SPEAKER ; 
 int /*<<< orphan*/  __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mach_is_hp6xx () ; 
 int /*<<< orphan*/  sh_dac_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dac_audio_start(void)
{
	if (mach_is_hp6xx()) {
		u16 v = __raw_readw(HD64461_GPADR);
		v &= ~HD64461_GPADR_SPEAKER;
		__raw_writew(v, HD64461_GPADR);
	}

	sh_dac_enable(CONFIG_SOUND_SH_DAC_AUDIO_CHANNEL);
}