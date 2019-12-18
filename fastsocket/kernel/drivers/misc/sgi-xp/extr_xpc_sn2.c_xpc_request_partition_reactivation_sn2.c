#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  activate_IRQ_nasid; } ;
struct TYPE_4__ {TYPE_1__ sn2; } ;
struct xpc_partition {TYPE_2__ sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpc_send_local_activate_IRQ_sn2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_request_partition_reactivation_sn2(struct xpc_partition *part)
{
	xpc_send_local_activate_IRQ_sn2(part->sn.sn2.activate_IRQ_nasid);
}