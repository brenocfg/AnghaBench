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
struct rpc_clnt {int dummy; } ;
struct nlm_host {struct rpc_clnt* h_rpcclnt; int /*<<< orphan*/  h_nsmhandle; int /*<<< orphan*/  h_count; int /*<<< orphan*/  h_lockowners; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nlm_host*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsm_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsm_unmonitor (struct nlm_host*) ; 
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_clnt*) ; 

__attribute__((used)) static void
nlm_destroy_host(struct nlm_host *host)
{
	struct rpc_clnt	*clnt;

	BUG_ON(!list_empty(&host->h_lockowners));
	BUG_ON(atomic_read(&host->h_count));

	nsm_unmonitor(host);
	nsm_release(host->h_nsmhandle);

	clnt = host->h_rpcclnt;
	if (clnt != NULL)
		rpc_shutdown_client(clnt);
	kfree(host);
}