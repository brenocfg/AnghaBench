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
struct rpc_pipe_msg {int len; int im_status; int /*<<< orphan*/  im_name; struct rpc_pipe_msg* data; int /*<<< orphan*/  im_id; int /*<<< orphan*/  im_conv; int /*<<< orphan*/  im_type; } ;
struct idmap_msg {int len; int im_status; int /*<<< orphan*/  im_name; struct idmap_msg* data; int /*<<< orphan*/  im_id; int /*<<< orphan*/  im_conv; int /*<<< orphan*/  im_type; } ;
struct idmap_hashtable {int /*<<< orphan*/  h_type; } ;
struct idmap_hashent {unsigned int ih_namelen; int /*<<< orphan*/  ih_name; } ;
struct idmap {int /*<<< orphan*/  idmap_lock; int /*<<< orphan*/  idmap_im_lock; int /*<<< orphan*/  idmap_wq; TYPE_1__* idmap_dentry; struct rpc_pipe_msg idmap_im; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  IDMAP_CONV_IDTONAME ; 
 int /*<<< orphan*/  IDMAP_NAMESZ ; 
 int IDMAP_STATUS_SUCCESS ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 struct idmap_hashent* idmap_lookup_id (struct idmap_hashtable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (struct rpc_pipe_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ rpc_queue_upcall (int /*<<< orphan*/ ,struct rpc_pipe_msg*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 unsigned int strnlen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wq ; 

__attribute__((used)) static int
nfs_idmap_name(struct idmap *idmap, struct idmap_hashtable *h,
		__u32 id, char *name)
{
	struct rpc_pipe_msg msg;
	struct idmap_msg *im;
	struct idmap_hashent *he;
	DECLARE_WAITQUEUE(wq, current);
	int ret = -EIO;
	unsigned int len;

	im = &idmap->idmap_im;

	mutex_lock(&idmap->idmap_lock);
	mutex_lock(&idmap->idmap_im_lock);

	he = idmap_lookup_id(h, id);
	if (he) {
		memcpy(name, he->ih_name, he->ih_namelen);
		ret = he->ih_namelen;
		goto out;
	}

	memset(im, 0, sizeof(*im));
	im->im_type = h->h_type;
	im->im_conv = IDMAP_CONV_IDTONAME;
	im->im_id = id;

	memset(&msg, 0, sizeof(msg));
	msg.data = im;
	msg.len = sizeof(*im);

	add_wait_queue(&idmap->idmap_wq, &wq);

	if (rpc_queue_upcall(idmap->idmap_dentry->d_inode, &msg) < 0) {
		remove_wait_queue(&idmap->idmap_wq, &wq);
		goto out;
	}

	set_current_state(TASK_UNINTERRUPTIBLE);
	mutex_unlock(&idmap->idmap_im_lock);
	schedule();
	__set_current_state(TASK_RUNNING);
	remove_wait_queue(&idmap->idmap_wq, &wq);
	mutex_lock(&idmap->idmap_im_lock);

	if (im->im_status & IDMAP_STATUS_SUCCESS) {
		if ((len = strnlen(im->im_name, IDMAP_NAMESZ)) == 0)
			goto out;
		memcpy(name, im->im_name, len);
		ret = len;
	}

 out:
	memset(im, 0, sizeof(*im));
	mutex_unlock(&idmap->idmap_im_lock);
	mutex_unlock(&idmap->idmap_lock);
	return ret;
}