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

/* Variables and functions */
 int RETRO_REGION_NTSC ; 
 int RETRO_REGION_PAL ; 
 scalar_t__ vdp_pal ; 

unsigned retro_get_region(void) { return vdp_pal ? RETRO_REGION_PAL : RETRO_REGION_NTSC; }