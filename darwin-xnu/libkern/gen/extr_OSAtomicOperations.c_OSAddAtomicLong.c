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
typedef  int /*<<< orphan*/  SInt64 ;
typedef  int /*<<< orphan*/  SInt32 ;

/* Variables and functions */
 scalar_t__ OSAddAtomic (int /*<<< orphan*/ ,long volatile*) ; 
 scalar_t__ OSAddAtomic64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

long
OSAddAtomicLong(long theAmount, volatile long *address)
{
#ifdef __LP64__
	return (long)OSAddAtomic64((SInt64)theAmount, (SInt64*)address);
#else
	return (long)OSAddAtomic((SInt32)theAmount, address);
#endif
}