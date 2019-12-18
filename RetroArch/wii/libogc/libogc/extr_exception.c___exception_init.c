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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ EX_DEC ; 
 scalar_t__ EX_FP ; 
 scalar_t__ EX_INT ; 
 int MSR_RI ; 
 scalar_t__ NUM_EXCEPTIONS ; 
 int /*<<< orphan*/  __exception_load (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __exception_sethandler (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_exceptionhandler ; 
 int /*<<< orphan*/  default_exceptionhandler ; 
 scalar_t__ exceptionhandler_end ; 
 int /*<<< orphan*/  exceptionhandler_patch ; 
 scalar_t__ exceptionhandler_start ; 
 int /*<<< orphan*/  fpu_exceptionhandler ; 
 int /*<<< orphan*/  irq_exceptionhandler ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mtmsr (int) ; 

void __exception_init()
{
	s32 i;
	// init all exceptions with the default handler & vector code
	for(i=0;i<NUM_EXCEPTIONS;i++) {
		// load default exception vector handler code
		__exception_load(i,exceptionhandler_start,(exceptionhandler_end-exceptionhandler_start),exceptionhandler_patch);
		//set default exception handler into table
		__exception_sethandler(i,default_exceptionhandler);
	}
	__exception_sethandler(EX_FP,fpu_exceptionhandler);
	__exception_sethandler(EX_INT,irq_exceptionhandler);
	__exception_sethandler(EX_DEC,dec_exceptionhandler);

	mtmsr(mfmsr()|MSR_RI);
}