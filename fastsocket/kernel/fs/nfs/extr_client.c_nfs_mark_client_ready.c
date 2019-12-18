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
struct nfs_client {int cl_cons_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_client_active_wq ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void nfs_mark_client_ready(struct nfs_client *clp, int state)
{
	clp->cl_cons_state = state;
	wake_up_all(&nfs_client_active_wq);
}