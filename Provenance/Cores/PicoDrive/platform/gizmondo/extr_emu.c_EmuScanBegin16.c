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
struct TYPE_2__ {int EmuOpt; } ;

/* Variables and functions */
 unsigned short* DrawLineDest ; 
 TYPE_1__ currentConfig ; 
 scalar_t__ giz_screen ; 

__attribute__((used)) static int EmuScanBegin16(unsigned int num)
{
	DrawLineDest = (unsigned short *) giz_screen + 321 * num;

	if ((currentConfig.EmuOpt&0x4000) && (num&1) == 0) // (Pico.m.frame_count&1))
		return 1; // skip next line

	return 0;
}