#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* reg; } ;
struct TYPE_4__ {TYPE_1__ video; } ;

/* Variables and functions */
 int POPT_EN_SOFTSCALE ; 
 TYPE_2__ Pico ; 
 int PicoOpt ; 
 int /*<<< orphan*/  g_screen_ptr ; 
 int /*<<< orphan*/  rot_buff ; 
 int /*<<< orphan*/  rotated_blit16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int EmuScanEnd16_rot(unsigned int num)
{
	if ((num & 3) != 3)
		return 0;
	rotated_blit16(g_screen_ptr, rot_buff, num + 1,
		!(Pico.video.reg[12] & 1) && !(PicoOpt & POPT_EN_SOFTSCALE));
	return 0;
}