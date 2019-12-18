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
 int ANTIC_margin ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * antic_memory ; 
 int anticmode ; 
 int* chars_read ; 
 int /*<<< orphan*/  dmactl_bug_chdata ; 
 int /*<<< orphan*/  draw_antic_0_dmactl_bug ; 
 int /*<<< orphan*/  draw_antic_2_dmactl_bug ; 
 int /*<<< orphan*/  draw_antic_ptr ; 
 int draw_antic_ptr_changed ; 
 size_t md ; 
 int /*<<< orphan*/  need_load ; 
 int /*<<< orphan*/  saved_draw_antic_ptr ; 

__attribute__((used)) static void set_dmactl_bug(void){
	need_load = FALSE;
	saved_draw_antic_ptr = draw_antic_ptr;
	draw_antic_ptr_changed = 1;
	if (anticmode == 2 || anticmode == 3 || anticmode == 0xf) {
		draw_antic_ptr = draw_antic_2_dmactl_bug;
		dmactl_bug_chdata = (anticmode == 0xf) ? 0 : antic_memory[ANTIC_margin + chars_read[md] - 1];
	}
	else {
		draw_antic_ptr = draw_antic_0_dmactl_bug;
	}
}