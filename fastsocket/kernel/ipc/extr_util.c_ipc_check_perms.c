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
struct kern_ipc_perm {int id; } ;
struct ipc_params {int /*<<< orphan*/  flg; } ;
struct ipc_ops {int (* associate ) (struct kern_ipc_perm*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ ipcperms (struct kern_ipc_perm*,int /*<<< orphan*/ ) ; 
 int stub1 (struct kern_ipc_perm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipc_check_perms(struct kern_ipc_perm *ipcp, struct ipc_ops *ops,
			struct ipc_params *params)
{
	int err;

	if (ipcperms(ipcp, params->flg))
		err = -EACCES;
	else {
		err = ops->associate(ipcp, params->flg);
		if (!err)
			err = ipcp->id;
	}

	return err;
}