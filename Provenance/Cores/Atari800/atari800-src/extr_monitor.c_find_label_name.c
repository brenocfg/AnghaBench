#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* name; scalar_t__ addr; } ;
typedef  TYPE_1__ symtable_rec ;
typedef  scalar_t__ UWORD ;
struct TYPE_6__ {scalar_t__ addr; char const* name; } ;

/* Variables and functions */
 scalar_t__ Atari800_MACHINE_5200 ; 
 scalar_t__ Atari800_machine_type ; 
 TYPE_1__* symtable_builtin ; 
 TYPE_1__* symtable_builtin_5200 ; 
 scalar_t__ symtable_builtin_enable ; 
 TYPE_2__* symtable_user ; 
 int symtable_user_size ; 

__attribute__((used)) static const char *find_label_name(UWORD addr, int is_write)
{
	int i;
	for (i = 0; i < symtable_user_size; i++) {
		if (symtable_user[i].addr == addr)
			return symtable_user[i].name;
	}
	if (symtable_builtin_enable) {
		const symtable_rec *p;
		for (p = (Atari800_machine_type == Atari800_MACHINE_5200 ? symtable_builtin_5200 : symtable_builtin); p->name != NULL; p++) {
			if (p->addr == addr) {
				if (is_write && p[1].addr == addr)
					p++;
				return p->name;
			}
		}
	}
	return NULL;
}