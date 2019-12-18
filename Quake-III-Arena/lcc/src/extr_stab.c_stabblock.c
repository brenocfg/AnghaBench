#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ x; } ;
typedef  scalar_t__ Symbol ;

/* Variables and functions */
 int /*<<< orphan*/ * IR ; 
 int /*<<< orphan*/  N_LBRAC ; 
 int /*<<< orphan*/  N_RBRAC ; 
 TYPE_2__* cfunc ; 
 int genlabel (int) ; 
 int /*<<< orphan*/  print (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  sparcIR ; 
 int /*<<< orphan*/  stabprefix ; 
 int /*<<< orphan*/  stabsym (int /*<<< orphan*/ ) ; 

void stabblock(int brace, int lev, Symbol *p) {
	if (brace == '{')
		while (*p)
			stabsym(*p++);
	if (IR == &sparcIR)
		print(".stabd 0x%x,0,%d\n", brace == '{' ? N_LBRAC : N_RBRAC, lev);
	else {
		int lab = genlabel(1);
		print(".stabn 0x%x,0,%d,%s%d-%s\n", brace == '{' ? N_LBRAC : N_RBRAC, lev,
			stabprefix, lab, cfunc->x.name);
		print("%s%d:\n", stabprefix, lab);
	}
}