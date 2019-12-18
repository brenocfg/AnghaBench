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
 int g_screen_height ; 
 scalar_t__ g_screen_ptr ; 
 int g_screen_width ; 
 int /*<<< orphan*/  memset32 (int*,int /*<<< orphan*/ ,int) ; 

void plat_status_msg_clear(void)
{
	unsigned short *d = (unsigned short *)g_screen_ptr + g_screen_width * g_screen_height;
	int l = g_screen_width * 8;
	memset32((int *)(d - l), 0, l * 2 / 4);
}