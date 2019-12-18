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
struct TYPE_3__ {size_t size; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ syment_t ;

/* Variables and functions */
 int nsyms ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* symbol_table ; 

size_t
sym_size(char *name)
{
	int i;
	syment_t *sep = symbol_table;

	for (i = 0; i < nsyms; i++) {
		if (strcmp(name, sep->name) == 0)
			return (sep->size);
		sep++;
	}
	return (0);
}