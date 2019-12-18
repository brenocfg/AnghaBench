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
 scalar_t__ has_colors () ; 
 int /*<<< orphan*/  no_colors_theme () ; 
 int /*<<< orphan*/  normal_color_theme () ; 
 int /*<<< orphan*/  set_normal_colors () ; 
 int /*<<< orphan*/  start_color () ; 
 int /*<<< orphan*/  use_default_colors () ; 

void set_colors(void)
{
	start_color();
	use_default_colors();
	set_normal_colors();
	if (has_colors()) {
		normal_color_theme();
	} else {
		/* give defaults */
		no_colors_theme();
	}
}