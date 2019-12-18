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
struct rpc_cred {unsigned long cr_flags; } ;
struct rpc_auth {int dummy; } ;
struct TYPE_2__ {scalar_t__ machine_cred; int /*<<< orphan*/ * group_info; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct generic_cred {struct rpc_cred gc_base; TYPE_1__ acred; } ;
struct auth_cred {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; scalar_t__ machine_cred; int /*<<< orphan*/ * group_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct rpc_cred* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long RPCAUTH_CRED_UPTODATE ; 
 int /*<<< orphan*/  dprintk (char*,char*,struct generic_cred*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_auth ; 
 int /*<<< orphan*/  generic_credops ; 
 int /*<<< orphan*/  get_group_info (int /*<<< orphan*/ *) ; 
 struct generic_cred* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpcauth_init_cred (struct rpc_cred*,struct auth_cred*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rpc_cred *
generic_create_cred(struct rpc_auth *auth, struct auth_cred *acred, int flags)
{
	struct generic_cred *gcred;

	gcred = kmalloc(sizeof(*gcred), GFP_KERNEL);
	if (gcred == NULL)
		return ERR_PTR(-ENOMEM);

	rpcauth_init_cred(&gcred->gc_base, acred, &generic_auth, &generic_credops);
	gcred->gc_base.cr_flags = 1UL << RPCAUTH_CRED_UPTODATE;

	gcred->acred.uid = acred->uid;
	gcred->acred.gid = acred->gid;
	gcred->acred.group_info = acred->group_info;
	if (gcred->acred.group_info != NULL)
		get_group_info(gcred->acred.group_info);
	gcred->acred.machine_cred = acred->machine_cred;

	dprintk("RPC:       allocated %s cred %p for uid %d gid %d\n",
			gcred->acred.machine_cred ? "machine" : "generic",
			gcred, acred->uid, acred->gid);
	return &gcred->gc_base;
}