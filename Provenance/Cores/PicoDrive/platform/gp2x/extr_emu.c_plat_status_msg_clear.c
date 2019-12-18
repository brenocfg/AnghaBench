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
 int EOPT_WIZ_TEAR_FIX ; 
 TYPE_1__ currentConfig ; 
 int /*<<< orphan*/  gp2x_memset_all_buffers (int,int,int) ; 
 scalar_t__* gp2x_screens ; 
 int /*<<< orphan*/  is_16bit_mode () ; 

void plat_status_msg_clear(void)
{
	int is_8bit = !is_16bit_mode();
	if (currentConfig.EmuOpt & EOPT_WIZ_TEAR_FIX) {
		/* ugh.. */
		int i, u, *p;
		if (is_8bit) {
			for (i = 0; i < 4; i++) {
				p = (int *)gp2x_screens[i] + (240-8) / 4;
				for (u = 320; u > 0; u--, p += 240/4)
					p[0] = p[1] = 0xe0e0e0e0;
			}
		} else {
			for (i = 0; i < 4; i++) {
				p = (int *)gp2x_screens[i] + (240-8)*2 / 4;
				for (u = 320; u > 0; u--, p += 240*2/4)
					p[0] = p[1] = p[2] = p[3] = 0;
			}
		}
		return;
	}

	if (is_8bit)
		gp2x_memset_all_buffers(320*232, 0xe0, 320*8);
	else
		gp2x_memset_all_buffers(320*232*2, 0, 320*8*2);
}