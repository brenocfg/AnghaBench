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
struct TYPE_3__ {int fpsr; int /*<<< orphan*/ * fType; } ;
typedef  TYPE_1__ FPA11 ;

/* Variables and functions */
 int BIT_AC ; 
 int FP_EMULATOR ; 
 TYPE_1__* GET_FPA11 () ; 
 int /*<<< orphan*/  typeNone ; 

__attribute__((used)) static void resetFPA11(void)
{
	int i;
	FPA11 *fpa11 = GET_FPA11();

	/* initialize the register type array */
	for (i = 0; i <= 7; i++) {
		fpa11->fType[i] = typeNone;
	}

	/* FPSR: set system id to FP_EMULATOR, set AC, clear all other bits */
	fpa11->fpsr = FP_EMULATOR | BIT_AC;
}