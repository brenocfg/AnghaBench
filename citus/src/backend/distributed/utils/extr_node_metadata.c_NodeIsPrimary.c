#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nodeRole; } ;
typedef  TYPE_1__ WorkerNode ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ InvalidOid ; 
 scalar_t__ PrimaryNodeRoleId () ; 

bool
NodeIsPrimary(WorkerNode *worker)
{
	Oid primaryRole = PrimaryNodeRoleId();

	/* if nodeRole does not yet exist, all nodes are primary nodes */
	if (primaryRole == InvalidOid)
	{
		return true;
	}

	return worker->nodeRole == primaryRole;
}