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
struct rpc_clnt {int /*<<< orphan*/  cl_count; int /*<<< orphan*/ * cl_auth; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_free_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpcauth_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rpc_free_auth(struct rpc_clnt *clnt)
{
	if (clnt->cl_auth == NULL) {
		rpc_free_client(clnt);
		return;
	}

	/*
	 * Note: RPCSEC_GSS may need to send NULL RPC calls in order to
	 *       release remaining GSS contexts. This mechanism ensures
	 *       that it can do so safely.
	 */
	atomic_inc(&clnt->cl_count);
	rpcauth_release(clnt->cl_auth);
	clnt->cl_auth = NULL;
	if (atomic_dec_and_test(&clnt->cl_count))
		rpc_free_client(clnt);
}