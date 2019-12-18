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
struct kern_ipc_perm {int /*<<< orphan*/  lock; scalar_t__ deleted; } ;
struct ipc_ids {int /*<<< orphan*/  ipcs_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct kern_ipc_perm* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct kern_ipc_perm* idr_find (int /*<<< orphan*/ *,int) ; 
 int ipcid_to_idx (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct kern_ipc_perm *ipc_lock(struct ipc_ids *ids, int id)
{
	struct kern_ipc_perm *out;
	int lid = ipcid_to_idx(id);

	rcu_read_lock();
	out = idr_find(&ids->ipcs_idr, lid);
	if (out == NULL) {
		rcu_read_unlock();
		return ERR_PTR(-EINVAL);
	}

	spin_lock(&out->lock);
	
	/* ipc_rmid() may have already freed the ID while ipc_lock
	 * was spinning: here verify that the structure is still valid
	 */
	if (out->deleted) {
		spin_unlock(&out->lock);
		rcu_read_unlock();
		return ERR_PTR(-EINVAL);
	}

	return out;
}