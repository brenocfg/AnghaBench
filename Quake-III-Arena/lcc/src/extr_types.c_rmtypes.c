#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* sym; } ;
struct TYPE_6__ {scalar_t__ op; TYPE_2__ u; } ;
struct entry {struct entry* link; TYPE_3__ type; } ;
struct TYPE_4__ {int scope; } ;

/* Variables and functions */
 scalar_t__ FUNCTION ; 
 int NELEMS (struct entry**) ; 
 int maxlevel ; 
 struct entry** typetable ; 

void rmtypes(int lev) {
	if (maxlevel >= lev) {
		int i;
		maxlevel = 0;
		for (i = 0; i < NELEMS(typetable); i++) {
			struct entry *tn, **tq = &typetable[i];
			while ((tn = *tq) != NULL)
				if (tn->type.op == FUNCTION)
					tq = &tn->link;
				else if (tn->type.u.sym && tn->type.u.sym->scope >= lev)
					*tq = tn->link;
				else {
					if (tn->type.u.sym && tn->type.u.sym->scope > maxlevel)
						maxlevel = tn->type.u.sym->scope;
					tq = &tn->link;
				}

		}
	}
}