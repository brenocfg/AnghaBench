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
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_client_mark_return_all_delegation_types (struct nfs_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_delegation_run_state_manager (struct nfs_client*) ; 

void nfs_expire_all_delegation_types(struct nfs_client *clp, fmode_t flags)
{
	nfs_client_mark_return_all_delegation_types(clp, flags);
	nfs_delegation_run_state_manager(clp);
}