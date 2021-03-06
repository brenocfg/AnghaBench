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
typedef  unsigned int u64 ;

/* Variables and functions */
 unsigned int XSTATE_FP ; 
 unsigned int XSTATE_SSE ; 
 unsigned int XSTATE_YMM ; 
 unsigned int host_xcr0 ; 

__attribute__((used)) static bool supported_xcr0_bit(unsigned bit)
{
	u64 mask = ((u64)1 << bit);

	return mask & (XSTATE_FP | XSTATE_SSE | XSTATE_YMM) & host_xcr0;
}