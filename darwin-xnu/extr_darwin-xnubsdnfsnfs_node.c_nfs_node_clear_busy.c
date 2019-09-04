#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_6__ {int /*<<< orphan*/  n_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int) ; 
 int ISSET (int /*<<< orphan*/ ,int) ; 
 int NBUSY ; 
 int NBUSYWANT ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

void
nfs_node_clear_busy(nfsnode_t np)
{
	int wanted;

	nfs_node_lock_force(np);
	wanted = ISSET(np->n_flag, NBUSYWANT);
	CLR(np->n_flag, NBUSY|NBUSYWANT);
	nfs_node_unlock(np);
	if (wanted)
		wakeup(np);
}