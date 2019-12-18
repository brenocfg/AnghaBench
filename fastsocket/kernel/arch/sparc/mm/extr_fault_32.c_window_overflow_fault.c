#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long* rwbuf_stkptrs; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  force_user_fault (unsigned long,int) ; 

void window_overflow_fault(void)
{
	unsigned long sp;

	sp = current_thread_info()->rwbuf_stkptrs[0];
	if(((sp + 0x38) & PAGE_MASK) != (sp & PAGE_MASK))
		force_user_fault(sp + 0x38, 1);
	force_user_fault(sp, 1);
}