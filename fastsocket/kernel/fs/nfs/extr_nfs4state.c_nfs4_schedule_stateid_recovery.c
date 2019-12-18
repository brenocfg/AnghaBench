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
struct nfs_server {struct nfs_client* nfs_client; } ;
struct nfs_client {int dummy; } ;
struct nfs4_state {int dummy; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  nfs4_schedule_state_manager (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs4_state_mark_reclaim_nograce (struct nfs_client*,struct nfs4_state*) ; 
 int /*<<< orphan*/  nfs4_valid_open_stateid (struct nfs4_state*) ; 

int nfs4_schedule_stateid_recovery(const struct nfs_server *server, struct nfs4_state *state)
{
	struct nfs_client *clp = server->nfs_client;

	if (!nfs4_valid_open_stateid(state))
		return -EBADF;
	nfs4_state_mark_reclaim_nograce(clp, state);
	nfs4_schedule_state_manager(clp);
	return 0;
}