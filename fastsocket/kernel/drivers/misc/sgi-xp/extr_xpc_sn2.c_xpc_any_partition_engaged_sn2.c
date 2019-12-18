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
typedef  int /*<<< orphan*/  u64 ;
struct amo {int /*<<< orphan*/  variable; } ;
struct TYPE_2__ {struct amo* amos_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  FETCHOP_LOAD ; 
 scalar_t__ FETCHOP_LOAD_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TO_AMO (int /*<<< orphan*/ ) ; 
 int XPC_ENGAGED_PARTITIONS_AMO_SN2 ; 
 TYPE_1__* xpc_vars_sn2 ; 

__attribute__((used)) static int
xpc_any_partition_engaged_sn2(void)
{
	struct amo *amo = xpc_vars_sn2->amos_page +
			  XPC_ENGAGED_PARTITIONS_AMO_SN2;

	/* our partition's amo variable */
	return FETCHOP_LOAD_OP(TO_AMO((u64)&amo->variable), FETCHOP_LOAD) != 0;
}