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
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ uv; } ;
struct TYPE_6__ {TYPE_2__ sn; } ;

/* Variables and functions */
 int XPC_P_ENGAGED_UV ; 
 TYPE_3__* xpc_partitions ; 

__attribute__((used)) static int
xpc_partition_engaged_uv(short partid)
{
	return (xpc_partitions[partid].sn.uv.flags & XPC_P_ENGAGED_UV) != 0;
}