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
struct menu {int dummy; } ;
struct gstr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  menu_get_ext_help (struct menu*,struct gstr*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  str_free (struct gstr*) ; 
 char* str_get (struct gstr*) ; 
 struct gstr str_new () ; 

__attribute__((used)) static void print_help(struct menu *menu)
{
	struct gstr help = str_new();

	menu_get_ext_help(menu, &help);

	printf("\n%s\n", str_get(&help));
	str_free(&help);
}