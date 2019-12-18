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
 scalar_t__ border_bottom ; 
 int /*<<< orphan*/  border_left ; 
 scalar_t__ border_right ; 
 int /*<<< orphan*/  border_top ; 
 int /*<<< orphan*/  g_menuscreen_h ; 
 int /*<<< orphan*/  g_menuscreen_w ; 

__attribute__((used)) static void menu_reset_borders(void)
{
	border_left = g_menuscreen_w;
	border_right = 0;
	border_top = g_menuscreen_h;
	border_bottom = 0;
}