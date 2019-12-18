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
struct rpc_auth {int dummy; } ;
struct qstr {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ rpc_authflavor_t ;

/* Variables and functions */
 scalar_t__ EIO ; 
 struct rpc_clnt* ERR_PTR (scalar_t__) ; 
 scalar_t__ IS_ERR (struct rpc_clnt*) ; 
 scalar_t__ nfs4_negotiate_security (struct inode*,struct qstr*) ; 
 struct rpc_clnt* rpc_clone_client (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_shutdown_client (struct rpc_clnt*) ; 
 struct rpc_auth* rpcauth_create (scalar_t__,struct rpc_clnt*) ; 

struct rpc_clnt *nfs4_create_sec_client(struct rpc_clnt *clnt, struct inode *inode,
					struct qstr *name)
{
	struct rpc_clnt *clone;
	struct rpc_auth *auth;
	rpc_authflavor_t flavor;

	flavor = nfs4_negotiate_security(inode, name);
	if (flavor < 0)
		return ERR_PTR(flavor);

	clone = rpc_clone_client(clnt);
	if (IS_ERR(clone))
		return clone;

	auth = rpcauth_create(flavor, clone);
	if (!auth) {
		rpc_shutdown_client(clone);
		clone = ERR_PTR(-EIO);
	}

	return clone;
}