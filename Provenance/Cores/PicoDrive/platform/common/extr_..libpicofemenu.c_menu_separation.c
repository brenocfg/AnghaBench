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
 scalar_t__ borders_pending ; 
 int /*<<< orphan*/  menu_darken_text_bg () ; 
 int /*<<< orphan*/  menu_reset_borders () ; 

__attribute__((used)) static void menu_separation(void)
{
	if (borders_pending) {
		menu_darken_text_bg();
		menu_reset_borders();
	}
}