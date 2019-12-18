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
 int /*<<< orphan*/  layer_fb ; 
 int /*<<< orphan*/  vout_fbdev_flip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenv_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void plat_video_flip(void)
{
	g_screen_ptr = vout_fbdev_flip(layer_fb);
	PicoDrawSetOutBuf(g_screen_ptr, g_screen_width * 2);

	// XXX: drain OS event queue here, maybe we'll actually use it someday..
	xenv_update(NULL, NULL, NULL, NULL);
}