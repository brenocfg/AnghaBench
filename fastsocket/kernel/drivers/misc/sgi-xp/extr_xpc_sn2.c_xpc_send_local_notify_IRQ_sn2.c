#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union xpc_channel_ctl_flags {int /*<<< orphan*/  all_flags; int /*<<< orphan*/ * flags; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {TYPE_1__* local_chctl_amo_va; } ;
struct TYPE_6__ {TYPE_2__ sn2; } ;
struct xpc_partition {TYPE_3__ sn; } ;
struct xpc_channel {size_t partid; size_t number; } ;
struct TYPE_4__ {int /*<<< orphan*/  variable; } ;

/* Variables and functions */
 int /*<<< orphan*/  FETCHOP_OR ; 
 int /*<<< orphan*/  FETCHOP_STORE_OP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TO_AMO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,size_t,size_t) ; 
 int /*<<< orphan*/  xpc_chan ; 
 struct xpc_partition* xpc_partitions ; 

__attribute__((used)) static void
xpc_send_local_notify_IRQ_sn2(struct xpc_channel *ch, u8 chctl_flag,
			      char *chctl_flag_string)
{
	struct xpc_partition *part = &xpc_partitions[ch->partid];
	union xpc_channel_ctl_flags chctl = { 0 };

	chctl.flags[ch->number] = chctl_flag;
	FETCHOP_STORE_OP(TO_AMO((u64)&part->sn.sn2.local_chctl_amo_va->
				variable), FETCHOP_OR, chctl.all_flags);
	dev_dbg(xpc_chan, "%s sent local from partid=%d, channel=%d\n",
		chctl_flag_string, ch->partid, ch->number);
}