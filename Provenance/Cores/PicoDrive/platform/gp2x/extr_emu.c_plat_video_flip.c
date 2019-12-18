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
 int /*<<< orphan*/  PicoDrawSetOutBuf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_screen_ptr ; 
 int g_screen_width ; 
 int /*<<< orphan*/  gp2x_video_flip () ; 
 scalar_t__ is_16bit_mode () ; 

void plat_video_flip(void)
{
	int stride = g_screen_width;
	gp2x_video_flip();

	if (is_16bit_mode())
		stride *= 2;
	PicoDrawSetOutBuf(g_screen_ptr, stride);
}