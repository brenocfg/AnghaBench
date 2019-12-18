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
struct TYPE_2__ {int EmuOpt; int /*<<< orphan*/  scaling; int /*<<< orphan*/  s_PicoOpt; } ;

/* Variables and functions */
 int EOPT_16BPP ; 
 int EOPT_VSYNC ; 
 int /*<<< orphan*/  POPT_EN_MCD_GFX ; 
 int /*<<< orphan*/  SCALE_2x2_3x2 ; 
 TYPE_1__ defaultConfig ; 

void pemu_prep_defconfig(void)
{
	defaultConfig.EmuOpt |= EOPT_VSYNC|EOPT_16BPP;
	defaultConfig.s_PicoOpt |= POPT_EN_MCD_GFX;
	defaultConfig.scaling = SCALE_2x2_3x2;
}