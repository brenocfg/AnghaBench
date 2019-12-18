#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpc_cred {int dummy; } ;
struct rpc_auth {TYPE_1__* au_ops; } ;
struct cred {int /*<<< orphan*/  group_info; int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;
struct auth_cred {int /*<<< orphan*/  group_info; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
typedef  int /*<<< orphan*/  acred ;
struct TYPE_2__ {struct rpc_cred* (* lookup_cred ) (struct rpc_auth*,struct auth_cred*,int) ;int /*<<< orphan*/  au_name; } ;

/* Variables and functions */
 struct cred* current_cred () ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_group_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct auth_cred*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_group_info (int /*<<< orphan*/ ) ; 
 struct rpc_cred* stub1 (struct rpc_auth*,struct auth_cred*,int) ; 

struct rpc_cred *
rpcauth_lookupcred(struct rpc_auth *auth, int flags)
{
	struct auth_cred acred;
	struct rpc_cred *ret;
	const struct cred *cred = current_cred();

	dprintk("RPC:       looking up %s cred\n",
		auth->au_ops->au_name);

	memset(&acred, 0, sizeof(acred));
	acred.uid = cred->fsuid;
	acred.gid = cred->fsgid;
	acred.group_info = get_group_info(((struct cred *)cred)->group_info);

	ret = auth->au_ops->lookup_cred(auth, &acred, flags);
	put_group_info(acred.group_info);
	return ret;
}