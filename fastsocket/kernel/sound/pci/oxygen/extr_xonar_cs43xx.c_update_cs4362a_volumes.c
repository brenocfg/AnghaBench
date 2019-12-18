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
typedef  int u8 ;
struct oxygen {int* dac_volume; scalar_t__ dac_mute; } ;

/* Variables and functions */
 int CS4362A_MUTE ; 
 int /*<<< orphan*/  cs4362a_write_cached (struct oxygen*,int,int) ; 

__attribute__((used)) static void update_cs4362a_volumes(struct oxygen *chip)
{
	unsigned int i;
	u8 mute;

	mute = chip->dac_mute ? CS4362A_MUTE : 0;
	for (i = 0; i < 6; ++i)
		cs4362a_write_cached(chip, 7 + i + i / 2,
				     (127 - chip->dac_volume[2 + i]) | mute);
}