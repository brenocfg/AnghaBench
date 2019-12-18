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
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int SDRAM_TREF ; 
 scalar_t__ cpu_is_pxa25x () ; 
 scalar_t__ cpu_is_pxa27x () ; 
 int sdram_rows ; 

__attribute__((used)) static u32 mdrefr_dri(unsigned int freq)
{
	u32 dri = 0;

	if (cpu_is_pxa25x())
		dri = ((freq * SDRAM_TREF) / (sdram_rows * 32));
	if (cpu_is_pxa27x())
		dri = ((freq * SDRAM_TREF) / (sdram_rows - 31)) / 32;
	return dri;
}