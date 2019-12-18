#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct TYPE_3__* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* symtable_user ; 
 size_t symtable_user_size ; 

__attribute__((used)) static void free_user_labels(void)
{
	if (symtable_user != NULL) {
		while (symtable_user_size > 0)
			free(symtable_user[--symtable_user_size].name);
		free(symtable_user);
		symtable_user = NULL;
	}
}