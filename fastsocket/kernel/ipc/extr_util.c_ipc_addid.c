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
typedef  int /*<<< orphan*/  uid_t ;
struct kern_ipc_perm {int /*<<< orphan*/  seq; int /*<<< orphan*/  id; int /*<<< orphan*/  cgid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  cuid; int /*<<< orphan*/  lock; scalar_t__ deleted; } ;
struct ipc_ids {int in_use; scalar_t__ seq; scalar_t__ seq_max; int /*<<< orphan*/  ipcs_idr; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int ENOSPC ; 
 int IPCMNI ; 
 int /*<<< orphan*/  current_euid_egid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int idr_get_new (int /*<<< orphan*/ *,struct kern_ipc_perm*,int*) ; 
 int /*<<< orphan*/  ipc_buildid (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ipc_addid(struct ipc_ids* ids, struct kern_ipc_perm* new, int size)
{
	uid_t euid;
	gid_t egid;
	int id, err;

	if (size > IPCMNI)
		size = IPCMNI;

	if (ids->in_use >= size)
		return -ENOSPC;

	spin_lock_init(&new->lock);
	new->deleted = 0;
	rcu_read_lock();
	spin_lock(&new->lock);

	err = idr_get_new(&ids->ipcs_idr, new, &id);
	if (err) {
		spin_unlock(&new->lock);
		rcu_read_unlock();
		return err;
	}

	ids->in_use++;

	current_euid_egid(&euid, &egid);
	new->cuid = new->uid = euid;
	new->gid = new->cgid = egid;

	new->seq = ids->seq++;
	if(ids->seq > ids->seq_max)
		ids->seq = 0;

	new->id = ipc_buildid(id, new->seq);
	return id;
}