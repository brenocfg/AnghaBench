#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nfs_client {int dummy; } ;
struct nfs4_state_recovery_ops {int /*<<< orphan*/  (* reclaim_complete ) (struct nfs_client*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nfs_client*) ; 

__attribute__((used)) static void nfs4_reclaim_complete(struct nfs_client *clp,
				 const struct nfs4_state_recovery_ops *ops)
{
	/* Notify the server we're done reclaiming our state */
	if (ops->reclaim_complete)
		(void)ops->reclaim_complete(clp);
}