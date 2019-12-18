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
struct TYPE_3__ {scalar_t__ sclass; scalar_t__ type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  N_LSYM ; 
 scalar_t__ TYPEDEF ; 
 int /*<<< orphan*/  dbxtype (scalar_t__) ; 
 int /*<<< orphan*/  print (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void stabtype(Symbol p) {
	if (p->type) {
		if (p->sclass == 0)
			dbxtype(p->type);
		else if (p->sclass == TYPEDEF)
			print(".stabs \"%s:t%d\",%d,0,0,0\n", p->name, dbxtype(p->type), N_LSYM);
	}
}