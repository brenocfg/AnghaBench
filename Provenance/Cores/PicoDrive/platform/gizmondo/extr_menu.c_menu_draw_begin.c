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
 scalar_t__ bg_buffer ; 
 int /*<<< orphan*/  memcpy32 (int*,int*,int) ; 
 scalar_t__ menu_screen ; 

void menu_draw_begin(int use_bgbuff)
{
	if (use_bgbuff)
		memcpy32((int *)menu_screen, (int *)bg_buffer, 321*240*2/4);
}