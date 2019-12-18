#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* activate_gru_mq_desc_gpa; void* heartbeat_gpa; } ;
struct TYPE_10__ {TYPE_3__ uv; } ;
struct xpc_rsvd_page {TYPE_4__ sn; } ;
struct TYPE_12__ {int /*<<< orphan*/ * gru_mq_desc; } ;
struct TYPE_7__ {int /*<<< orphan*/  cached_heartbeat; } ;
struct TYPE_8__ {TYPE_1__ uv; } ;
struct TYPE_11__ {TYPE_2__ sn; } ;

/* Variables and functions */
 size_t sn_partition_id ; 
 void* uv_gpa (int /*<<< orphan*/ *) ; 
 TYPE_6__* xpc_activate_mq_uv ; 
 int /*<<< orphan*/ * xpc_heartbeat_uv ; 
 TYPE_5__* xpc_partitions ; 

__attribute__((used)) static int
xpc_setup_rsvd_page_uv(struct xpc_rsvd_page *rp)
{
	xpc_heartbeat_uv =
	    &xpc_partitions[sn_partition_id].sn.uv.cached_heartbeat;
	rp->sn.uv.heartbeat_gpa = uv_gpa(xpc_heartbeat_uv);
	rp->sn.uv.activate_gru_mq_desc_gpa =
	    uv_gpa(xpc_activate_mq_uv->gru_mq_desc);
	return 0;
}