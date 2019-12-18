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
typedef  int /*<<< orphan*/  uint64 ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ palloc0 (int) ; 

__attribute__((used)) static uint64 *
AllocateUint64(uint64 value)
{
	uint64 *allocatedValue = (uint64 *) palloc0(sizeof(uint64));
	Assert(sizeof(uint64) >= 8);

	(*allocatedValue) = value;

	return allocatedValue;
}