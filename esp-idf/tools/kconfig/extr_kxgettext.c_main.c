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
 int /*<<< orphan*/  conf_parse (char*) ; 
 int /*<<< orphan*/  menu__xgettext () ; 
 int /*<<< orphan*/  menu_build_message_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_get_root_menu (int /*<<< orphan*/ *) ; 

int main(int ac, char **av)
{
	conf_parse(av[1]);

	menu_build_message_list(menu_get_root_menu(NULL));
	menu__xgettext();
	return 0;
}