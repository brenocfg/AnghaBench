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
 int /*<<< orphan*/  plat_status_msg_busy_next (char const*) ; 

void plat_status_msg_busy_first(const char *msg)
{
//	memset32(g_screen_ptr, 0, g_screen_width * g_screen_height * 2 / 4);
	plat_status_msg_busy_next(msg);
}