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
 int* fb_paddr ; 
 size_t fb_work_buf ; 
 int /*<<< orphan*/  g_screen_ptr ; 
 int /*<<< orphan*/ * gp2x_screens ; 
 int* memregl ; 

__attribute__((used)) static void pollux_video_flip(int buf_count)
{
	memregl[0x406C>>2] = memregl[0x446C>>2] = fb_paddr[fb_work_buf];
	memregl[0x4058>>2] |= 0x10;
	memregl[0x4458>>2] |= 0x10;

	fb_work_buf++;
	if (fb_work_buf >= buf_count)
		fb_work_buf = 0;
	g_screen_ptr = gp2x_screens[fb_work_buf];
}