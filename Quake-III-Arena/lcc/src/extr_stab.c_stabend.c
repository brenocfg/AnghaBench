#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* segment ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  Symbol ;
typedef  int /*<<< orphan*/  Coordinate ;

/* Variables and functions */
 int /*<<< orphan*/  CODE ; 
 TYPE_1__* IR ; 
 int /*<<< orphan*/  N_SO ; 
 int /*<<< orphan*/  print (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stabprefix ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void stabend(Coordinate *cp, Symbol p, Coordinate **cpp, Symbol *sp, Symbol *stab) {
	(*IR->segment)(CODE);
	print(".stabs \"\", %d, 0, 0,%setext\n", N_SO, stabprefix);
	print("%setext:\n", stabprefix);
}