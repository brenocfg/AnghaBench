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
typedef  int /*<<< orphan*/  word ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ IS_64BIT_PROCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ copyout (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_proc () ; 
 int suiword (int /*<<< orphan*/ ,long) ; 

int
sulong(user_addr_t addr, int64_t word)
{

	if (IS_64BIT_PROCESS(current_proc())) {
		return(copyout((void *)&word, addr, sizeof(word)) == 0 ? 0 : -1);
	} else {
		return(suiword(addr, (long)word));
	}
}