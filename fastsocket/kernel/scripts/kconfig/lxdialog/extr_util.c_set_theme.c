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
 int /*<<< orphan*/  set_blackbg_theme () ; 
 int /*<<< orphan*/  set_bluetitle_theme () ; 
 int /*<<< orphan*/  set_classic_theme () ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int set_theme(const char *theme)
{
	int use_color = 1;
	if (!theme)
		set_bluetitle_theme();
	else if (strcmp(theme, "classic") == 0)
		set_classic_theme();
	else if (strcmp(theme, "bluetitle") == 0)
		set_bluetitle_theme();
	else if (strcmp(theme, "blackbg") == 0)
		set_blackbg_theme();
	else if (strcmp(theme, "mono") == 0)
		use_color = 0;

	return use_color;
}