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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;

/* Variables and functions */
 int EPSW_FLAG_Z ; 

__attribute__((used)) static int mask_test_and_clear(volatile u8 *ptr, u8 mask)
{
	u32 epsw;
	asm volatile("	bclr	%1,(%2)		\n"
		     "	mov	epsw,%0		\n"
		     : "=d"(epsw) : "d"(mask), "a"(ptr));
	return !(epsw & EPSW_FLAG_Z);
}