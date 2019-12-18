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
struct TYPE_2__ {int* instructionPointers; } ;

/* Variables and functions */
 int /*<<< orphan*/  InstImm (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  PPC_ADDI ; 
 int /*<<< orphan*/  PPC_LWZ ; 
 int PPC_STW ; 
 int PPC_STWU ; 
 int R_OPSTACK ; 
 int R_SECOND ; 
 int R_TOP ; 
 int* buf ; 
 int compiledOfs ; 
 size_t instruction ; 
 scalar_t__* jused ; 
 int /*<<< orphan*/  ltop () ; 
 scalar_t__ pass ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  rtopped ; 
 TYPE_1__* tvm ; 

__attribute__((used)) static void ltopandsecond() {
    if (pass>=0 && buf[compiledOfs-1] == (PPC_STWU |  R_TOP<<21 | R_OPSTACK<<16 | 4 ) && jused[instruction]==0 ) {
	compiledOfs--;
	if (!pass) {
	    tvm->instructionPointers[instruction] = compiledOfs * 4;
	}
	InstImm( PPC_LWZ, R_SECOND, R_OPSTACK, 0 );	// get value from opstack
	InstImm( PPC_ADDI, R_OPSTACK, R_OPSTACK, -4 );
    } else if (pass>=0 && buf[compiledOfs-1] == (PPC_STW |  R_TOP<<21 | R_OPSTACK<<16 | 0 )  && jused[instruction]==0 ) {
	compiledOfs--;
	if (!pass) {
	    tvm->instructionPointers[instruction] = compiledOfs * 4;
	}
	InstImm( PPC_LWZ, R_SECOND, R_OPSTACK, -4 );	// get value from opstack
	InstImm( PPC_ADDI, R_OPSTACK, R_OPSTACK, -8 );
    } else {
	ltop();		// get value from opstack
	InstImm( PPC_LWZ, R_SECOND, R_OPSTACK, -4 );	// get value from opstack
	InstImm( PPC_ADDI, R_OPSTACK, R_OPSTACK, -8 );
    }
    rtopped = qfalse;
}