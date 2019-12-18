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
 void* VRAM_FB0 ; 
 void* VRAM_FB1 ; 
 scalar_t__ current_screen ; 

void *psp_video_get_active_fb(void)
{
	return current_screen ? VRAM_FB1 : VRAM_FB0;
}