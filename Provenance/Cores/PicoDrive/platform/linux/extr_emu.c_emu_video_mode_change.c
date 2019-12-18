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
 int /*<<< orphan*/  g_screen_ptr ; 
 int g_screen_width ; 
 int /*<<< orphan*/  memset32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void emu_video_mode_change(int start_line, int line_count, int is_32cols)
{
	// clear whole screen in all buffers
	memset32(g_screen_ptr, 0, g_screen_width * g_screen_height * 2 / 4);
}