#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int get; } ;
struct TYPE_5__ {int put; } ;
struct TYPE_7__ {TYPE_2__ w_local_GP; TYPE_1__ w_remote_GP; } ;
struct TYPE_8__ {TYPE_3__ sn2; } ;
struct xpc_channel {TYPE_4__ sn; } ;

/* Variables and functions */

__attribute__((used)) static int
xpc_n_of_deliverable_payloads_sn2(struct xpc_channel *ch)
{
	return ch->sn.sn2.w_remote_GP.put - ch->sn.sn2.w_local_GP.get;
}