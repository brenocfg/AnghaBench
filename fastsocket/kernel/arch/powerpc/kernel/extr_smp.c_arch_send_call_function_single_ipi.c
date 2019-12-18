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
struct TYPE_2__ {int /*<<< orphan*/  (* message_pass ) (int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PPC_MSG_CALL_FUNC_SINGLE ; 
 TYPE_1__* smp_ops ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

void arch_send_call_function_single_ipi(int cpu)
{
	smp_ops->message_pass(cpu, PPC_MSG_CALL_FUNC_SINGLE);
}