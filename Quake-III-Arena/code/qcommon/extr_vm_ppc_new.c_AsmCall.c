#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

void AsmCall( void ) {
asm (
     // pop off the destination instruction
"    lwz		r12,0(r4)	\n"	// RG_TOP, 0(RG_OPSTACK)
"    addi	r4,r4,-4		\n"	// RG_OPSTACK, RG_OPSTACK, -4 \n"

    // see if it is a system trap
"    cmpwi	r12,0			\n"	// RG_TOP, 0 \n"
"    bc		12,0, systemTrap	\n"

    // calling another VM function, so lookup in instructionPointers
"    slwi	r12,r12,2		\n"	// RG_TOP,RG_TOP,2
                        // FIXME: range check
"    lwzx	r12, r8, r12		\n"	// RG_TOP, RG_INSTRUCTIONS(RG_TOP)	
"    mtctr	r12			\n"	// RG_TOP
);

#if defined(MACOS_X) && defined(__OPTIMIZE__)
    // On Mac OS X, gcc doesn't push a frame when we are optimized, so trying to tear it down results in grave disorder.
#warning Mac OS X optimization on, not popping GCC AsmCall frame
#else
    // Mac OS X Server and unoptimized compiles include a GCC AsmCall frame
    asm (
"	lwz		r1,0(r1)	\n"	// pop off the GCC AsmCall frame
"	lmw		r30,-8(r1)	\n"
);
#endif

asm (
"	    bcctr	20,0		\n" // when it hits a leave, it will branch to the current link register

    // calling a system trap
"systemTrap:				\n"
	// convert to positive system call number
"	subfic	r12,r12,-1		\n"

    // save all our registers, including the current link register
"    mflr	r13			\n"	// RG_SECOND		// copy off our link register
"	addi	r1,r1,-92		\n"	// required 24 byets of linkage, 32 bytes of parameter, plus our saves
"    stw		r3,56(r1)	\n"	// RG_STACK, -36(REAL_STACK)
"    stw		r4,60(r1)	\n"	// RG_OPSTACK, 4(RG_REAL_STACK)
"    stw		r5,64(r1)	\n"	// RG_MEMBASE, 8(RG_REAL_STACK)
"    stw		r6,68(r1)	\n"	// RG_MEMMASK, 12(RG_REAL_STACK)
"    stw		r7,72(r1)	\n"	// RG_ASMCALL, 16(RG_REAL_STACK)
"    stw		r8,76(r1)	\n"	// RG_INSTRUCTIONS, 20(RG_REAL_STACK)
"    stw		r9,80(r1)	\n"	// RG_NUM_INSTRUCTIONS, 24(RG_REAL_STACK)
"    stw		r10,84(r1)	\n"	// RG_VM, 28(RG_REAL_STACK)
"    stw		r13,88(r1)	\n"	// RG_SECOND, 32(RG_REAL_STACK)	// link register

    // save the vm stack position to allow recursive VM entry
"    addi	r13,r3,-4		\n"	// RG_TOP, RG_STACK, -4
"    stw		r13,0(r10)	\n"	//RG_TOP, VM_OFFSET_PROGRAM_STACK(RG_VM)

    // save the system call number as the 0th parameter
"    add		r3,r3,r5	\n"	// r3,  RG_STACK, RG_MEMBASE		// r3 is the first parameter to vm->systemCalls
"    stwu	r12,4(r3)		\n"	// RG_TOP, 4(r3)

    // make the system call with the address of all the VM parms as a parameter
    // vm->systemCalls( &parms )
"    lwz		r12,4(r10)	\n"	// RG_TOP, VM_OFFSET_SYSTEM_CALL(RG_VM)
"    mtctr	r12			\n"	// RG_TOP
"    bcctrl	20,0			\n"
"    mr		r12,r3			\n"	// RG_TOP, r3

    // pop our saved registers
"   	lwz		r3,56(r1)	\n"	// RG_STACK, 0(RG_REAL_STACK)
"   	lwz		r4,60(r1)	\n"	// RG_OPSTACK, 4(RG_REAL_STACK)
"   	lwz		r5,64(r1)	\n"	// RG_MEMBASE, 8(RG_REAL_STACK)
"   	lwz		r6,68(r1)	\n"	// RG_MEMMASK, 12(RG_REAL_STACK)
"   	lwz		r7,72(r1)	\n"	// RG_ASMCALL, 16(RG_REAL_STACK)
"   	lwz		r8,76(r1)	\n"	// RG_INSTRUCTIONS, 20(RG_REAL_STACK)
"   	lwz		r9,80(r1)	\n"	// RG_NUM_INSTRUCTIONS, 24(RG_REAL_STACK)
"   	lwz		r10,84(r1)	\n"	// RG_VM, 28(RG_REAL_STACK)
"   	lwz		r13,88(r1)	\n"	// RG_SECOND, 32(RG_REAL_STACK)
"    addi	r1,r1,92		\n"	// RG_REAL_STACK, RG_REAL_STACK, 36

    // restore the old link register
"    mtlr	r13			\n"	// RG_SECOND

    // save off the return value
"    stwu	r12,4(r4)		\n"	// RG_TOP, 0(RG_OPSTACK)

	// GCC adds its own prolog / epliog code
 );
}