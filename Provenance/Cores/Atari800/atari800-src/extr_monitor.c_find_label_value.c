#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int addr; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ symtable_rec ;

/* Variables and functions */
 scalar_t__ Atari800_MACHINE_5200 ; 
 scalar_t__ Atari800_machine_type ; 
 scalar_t__ Util_stricmp (int /*<<< orphan*/ *,char const*) ; 
 TYPE_1__* find_user_label (char const*) ; 
 TYPE_1__* symtable_builtin ; 
 TYPE_1__* symtable_builtin_5200 ; 
 scalar_t__ symtable_builtin_enable ; 

__attribute__((used)) static int find_label_value(const char *name)
{
	const symtable_rec *p = find_user_label(name);
	if (p != NULL)
		return p->addr;
	if (symtable_builtin_enable) {
		for (p = (Atari800_machine_type == Atari800_MACHINE_5200 ? symtable_builtin_5200 : symtable_builtin); p->name != NULL; p++) {
			if (Util_stricmp(p->name, name) == 0)
				return p->addr;
		}
	}
	return -1;
}