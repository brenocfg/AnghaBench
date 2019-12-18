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
 int /*<<< orphan*/  PSP_DISPLAY_PIXEL_FORMAT_565 ; 
 int /*<<< orphan*/  PSP_DISPLAY_SETBUF_NEXTFRAME ; 
 int /*<<< orphan*/  VRAM_FB0 ; 
 scalar_t__ current_screen ; 
 int /*<<< orphan*/  psp_screen ; 
 int /*<<< orphan*/  sceDisplaySetFrameBuf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void psp_video_switch_to_single(void)
{
	psp_screen = VRAM_FB0;
	sceDisplaySetFrameBuf(psp_screen, 512, PSP_DISPLAY_PIXEL_FORMAT_565, PSP_DISPLAY_SETBUF_NEXTFRAME);
	current_screen = 0;
}