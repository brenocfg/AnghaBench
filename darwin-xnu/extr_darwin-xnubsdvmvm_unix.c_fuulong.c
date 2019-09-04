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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  ulongword ;
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 scalar_t__ IS_64BIT_PROCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ copyin (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  current_proc () ; 
 scalar_t__ fuiword (int /*<<< orphan*/ ) ; 

uint64_t
fuulong(user_addr_t addr)
{
	uint64_t ulongword;

	if (IS_64BIT_PROCESS(current_proc())) {
		if (copyin(addr, (void *)&ulongword, sizeof(ulongword)) != 0)
			return(-1ULL);
		return(ulongword);
	} else {
		return((uint64_t)fuiword(addr));
	}
}