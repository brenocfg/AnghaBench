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
 int /*<<< orphan*/  init_debug () ; 
 int select_menu_item (char) ; 
 int show_help () ; 
 int strlen (char*) ; 

int main(int argc, char *argv[])
{
	init_debug();

	if (argc != 2 || strlen(argv[1]) != 2 || argv[1][0] != '-')
		return show_help();

	return select_menu_item(argv[1][1]);
}