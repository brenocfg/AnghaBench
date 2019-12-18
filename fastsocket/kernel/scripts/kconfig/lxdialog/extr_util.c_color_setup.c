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
 int /*<<< orphan*/  init_dialog_colors () ; 
 int /*<<< orphan*/  set_mono_theme () ; 
 int set_theme (char const*) ; 
 int /*<<< orphan*/  start_color () ; 

__attribute__((used)) static void color_setup(const char *theme)
{
	int use_color;

	use_color = set_theme(theme);
	if (use_color && has_colors()) {
		start_color();
		init_dialog_colors();
	} else
		set_mono_theme();
}