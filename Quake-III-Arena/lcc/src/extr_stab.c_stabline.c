#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_1__ x; } ;
struct TYPE_6__ {scalar_t__ file; int y; } ;
typedef  TYPE_2__ Coordinate ;

/* Variables and functions */
 int /*<<< orphan*/ * IR ; 
 int /*<<< orphan*/  N_SLINE ; 
 int /*<<< orphan*/  N_SOL ; 
 TYPE_4__* cfunc ; 
 scalar_t__ currentfile ; 
 int genlabel (int) ; 
 int /*<<< orphan*/  print (char*,scalar_t__,int,...) ; 
 int /*<<< orphan*/  sparcIR ; 
 int /*<<< orphan*/  stabprefix ; 

void stabline(Coordinate *cp) {
	if (cp->file && cp->file != currentfile) {
		int lab = genlabel(1);
		print(".stabs \"%s\",0x%x,0,0,%s%d\n", cp->file, N_SOL, stabprefix, lab);
		print("%s%d:\n", stabprefix, lab);
		currentfile = cp->file;
	}
	if (IR == &sparcIR)
		print(".stabd 0x%x,0,%d\n", N_SLINE, cp->y);
	else {
		int lab = genlabel(1);
		print(".stabn 0x%x,0,%d,%s%d-%s\n", N_SLINE, cp->y,
			stabprefix, lab, cfunc->x.name);
		print("%s%d:\n", stabprefix, lab);
	}
}