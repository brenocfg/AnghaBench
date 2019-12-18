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
struct rpc_cred {int dummy; } ;
struct rpc_auth {int dummy; } ;
struct auth_cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_auth ; 
 struct rpc_cred* rpcauth_lookup_credcache (int /*<<< orphan*/ *,struct auth_cred*,int) ; 

__attribute__((used)) static struct rpc_cred *
generic_lookup_cred(struct rpc_auth *auth, struct auth_cred *acred, int flags)
{
	return rpcauth_lookup_credcache(&generic_auth, acred, flags);
}