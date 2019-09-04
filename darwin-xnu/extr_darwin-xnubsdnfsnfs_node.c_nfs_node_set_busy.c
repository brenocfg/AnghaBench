#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thread_t ;
struct timespec {int member_0; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_7__ {int /*<<< orphan*/  n_flag; int /*<<< orphan*/  n_lock; } ;

/* Variables and functions */
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBUSY ; 
 int /*<<< orphan*/  NBUSYWANT ; 
 int /*<<< orphan*/  NFSTONMP (TYPE_1__*) ; 
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__,char*,struct timespec*) ; 
 int nfs_node_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 
 int nfs_sigintr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nfs_node_set_busy(nfsnode_t np, thread_t thd)
{
	struct timespec ts = { 2, 0 };
	int error;

	if ((error = nfs_node_lock(np)))
		return (error);
	while (ISSET(np->n_flag, NBUSY)) {
		SET(np->n_flag, NBUSYWANT);
		msleep(np, &np->n_lock, PZERO-1, "nfsbusywant", &ts);
		if ((error = nfs_sigintr(NFSTONMP(np), NULL, thd, 0)))
			break;
	}
	if (!error)
		SET(np->n_flag, NBUSY);
	nfs_node_unlock(np);
	return (error);
}