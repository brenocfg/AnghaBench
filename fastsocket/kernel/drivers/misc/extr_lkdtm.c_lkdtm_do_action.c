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
typedef  int u8 ;
typedef  int u32 ;
typedef  enum ctype { ____Placeholder_ctype } ctype ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CT_BUG 140 
#define  CT_CORRUPT_STACK 139 
#define  CT_EXCEPTION 138 
#define  CT_HARDLOCKUP 137 
#define  CT_HUNG_TASK 136 
#define  CT_LOOP 135 
#define  CT_NONE 134 
#define  CT_OVERFLOW 133 
#define  CT_OVERWRITE_ALLOCATION 132 
#define  CT_PANIC 131 
#define  CT_SOFTLOCKUP 130 
#define  CT_UNALIGNED_LOAD_STORE_WRITE 129 
#define  CT_WRITE_AFTER_FREE 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  memset (int*,int,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  recursive_loop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lkdtm_do_action(enum ctype which)
{
	switch (which) {
	case CT_PANIC:
		panic("dumptest");
		break;
	case CT_BUG:
		BUG();
		break;
	case CT_EXCEPTION:
		*((int *) 0) = 0;
		break;
	case CT_LOOP:
		for (;;)
			;
		break;
	case CT_OVERFLOW:
		(void) recursive_loop(0);
		break;
	case CT_CORRUPT_STACK: {
		volatile u32 data[8];
		volatile u32 *p = data;

		p[12] = 0x12345678;
		break;
	}
	case CT_UNALIGNED_LOAD_STORE_WRITE: {
		static u8 data[5] __attribute__((aligned(4))) = {1, 2,
				3, 4, 5};
		u32 *p;
		u32 val = 0x12345678;

		p = (u32 *)(data + 1);
		if (*p == 0)
			val = 0x87654321;
		*p = val;
		 break;
	}
	case CT_OVERWRITE_ALLOCATION: {
		size_t len = 1020;
		u32 *data = kmalloc(len, GFP_KERNEL);

		data[1024 / sizeof(u32)] = 0x12345678;
		kfree(data);
		break;
	}
	case CT_WRITE_AFTER_FREE: {
		size_t len = 1024;
		u32 *data = kmalloc(len, GFP_KERNEL);

		kfree(data);
		schedule();
		memset(data, 0x78, len);
		break;
	}
	case CT_SOFTLOCKUP:
		preempt_disable();
		for (;;)
			cpu_relax();
		break;
	case CT_HARDLOCKUP:
		local_irq_disable();
		for (;;)
			cpu_relax();
		break;
	case CT_HUNG_TASK:
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule();
		break;
	case CT_NONE:
	default:
		break;
	}

}