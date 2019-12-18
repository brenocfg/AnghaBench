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
typedef  size_t u32 ;
struct rpc_clnt {struct rpc_auth* cl_auth; } ;
struct rpc_authops {int /*<<< orphan*/  owner; struct rpc_auth* (* create ) (struct rpc_clnt*,int /*<<< orphan*/ ) ;} ;
struct rpc_auth {int dummy; } ;
typedef  int /*<<< orphan*/  rpc_authflavor_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct rpc_auth* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct rpc_auth*) ; 
 size_t RPC_AUTH_MAXFLAVOR ; 
 struct rpc_authops** auth_flavors ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 size_t pseudoflavor_to_flavor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*,size_t) ; 
 int /*<<< orphan*/  rpc_authflavor_lock ; 
 int /*<<< orphan*/  rpcauth_release (struct rpc_auth*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct rpc_auth* stub1 (struct rpc_clnt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct rpc_auth *
rpcauth_create(rpc_authflavor_t pseudoflavor, struct rpc_clnt *clnt)
{
	struct rpc_auth		*auth;
	const struct rpc_authops *ops;
	u32			flavor = pseudoflavor_to_flavor(pseudoflavor);

	auth = ERR_PTR(-EINVAL);
	if (flavor >= RPC_AUTH_MAXFLAVOR)
		goto out;

	if ((ops = auth_flavors[flavor]) == NULL)
		request_module("rpc-auth-%u", flavor);
	spin_lock(&rpc_authflavor_lock);
	ops = auth_flavors[flavor];
	if (ops == NULL || !try_module_get(ops->owner)) {
		spin_unlock(&rpc_authflavor_lock);
		goto out;
	}
	spin_unlock(&rpc_authflavor_lock);
	auth = ops->create(clnt, pseudoflavor);
	module_put(ops->owner);
	if (IS_ERR(auth))
		return auth;
	if (clnt->cl_auth)
		rpcauth_release(clnt->cl_auth);
	clnt->cl_auth = auth;

out:
	return auth;
}