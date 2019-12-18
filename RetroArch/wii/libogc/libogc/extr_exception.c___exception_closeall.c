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
 int MSR_EE ; 
 int MSR_FP ; 
 int MSR_RI ; 
 scalar_t__ NUM_EXCEPTIONS ; 
 int /*<<< orphan*/  __exception_close (scalar_t__) ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mtmsr (int) ; 

void __exception_closeall()
{
	s32 i;

	mtmsr(mfmsr()&~MSR_EE);
	mtmsr(mfmsr()|(MSR_FP|MSR_RI));

	for(i=0;i<NUM_EXCEPTIONS;i++) {
		__exception_close(i);
	}
}