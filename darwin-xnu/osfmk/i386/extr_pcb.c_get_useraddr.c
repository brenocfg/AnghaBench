#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rip; } ;
struct TYPE_7__ {TYPE_1__ isf; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
struct TYPE_8__ {int /*<<< orphan*/  eip; } ;
typedef  TYPE_3__ x86_saved_state32_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  thread_t ;

/* Variables and functions */
 TYPE_3__* USER_REGS32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* USER_REGS64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ thread_is_64bit_addr (int /*<<< orphan*/ ) ; 

user_addr_t
get_useraddr(void)
{
        thread_t thr_act = current_thread();
 
        if (thread_is_64bit_addr(thr_act)) {
	        x86_saved_state64_t	*iss64;
		
		iss64 = USER_REGS64(thr_act);

         	return(iss64->isf.rip);
	} else {
	        x86_saved_state32_t	*iss32;

		iss32 = USER_REGS32(thr_act);

         	return(iss32->eip);
	}
}