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
struct TYPE_4__ {int /*<<< orphan*/  put; } ;
struct TYPE_5__ {TYPE_1__ w_local_GP; } ;
struct TYPE_6__ {TYPE_2__ sn2; } ;
struct xpc_channel {TYPE_3__ sn; int /*<<< orphan*/  reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpc_notify_senders_sn2 (struct xpc_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xpc_notify_senders_of_disconnect_sn2(struct xpc_channel *ch)
{
	xpc_notify_senders_sn2(ch, ch->reason, ch->sn.sn2.w_local_GP.put);
}