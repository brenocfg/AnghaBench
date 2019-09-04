#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_5__ {int /*<<< orphan*/  n_lock; scalar_t__ n_hflag; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  FSDBG_BOT (int,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NHHASHED ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 

int
nfs_node_lock_internal(nfsnode_t np, int force)
{
	FSDBG_TOP(268, np, force, 0, 0);
	lck_mtx_lock(&np->n_lock);
	if (!force && !(np->n_hflag && NHHASHED)) {
		FSDBG_BOT(268, np, 0xdead, 0, 0);
		lck_mtx_unlock(&np->n_lock);
		return (ENOENT);
	}
	FSDBG_BOT(268, np, force, 0, 0);
	return (0);
}