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
struct print_flag_sym {struct print_flag_sym* str; struct print_flag_sym* value; struct print_flag_sym* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct print_flag_sym*) ; 

__attribute__((used)) static void free_flag_sym(struct print_flag_sym *fsym)
{
	struct print_flag_sym *next;

	while (fsym) {
		next = fsym->next;
		free(fsym->value);
		free(fsym->str);
		free(fsym);
		fsym = next;
	}
}