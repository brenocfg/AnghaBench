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
struct kern_ipc_perm {int dummy; } ;
struct ipc_ids {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIDRM ; 
 struct kern_ipc_perm* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct kern_ipc_perm*) ; 
 scalar_t__ ipc_checkid (struct kern_ipc_perm*,int) ; 
 struct kern_ipc_perm* ipc_lock (struct ipc_ids*,int) ; 
 int /*<<< orphan*/  ipc_unlock (struct kern_ipc_perm*) ; 

struct kern_ipc_perm *ipc_lock_check(struct ipc_ids *ids, int id)
{
	struct kern_ipc_perm *out;

	out = ipc_lock(ids, id);
	if (IS_ERR(out))
		return out;

	if (ipc_checkid(out, id)) {
		ipc_unlock(out);
		return ERR_PTR(-EIDRM);
	}

	return out;
}