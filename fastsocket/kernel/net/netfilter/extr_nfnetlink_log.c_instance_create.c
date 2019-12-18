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
typedef  int /*<<< orphan*/  u_int16_t ;
struct nfulnl_instance {int peer_pid; int /*<<< orphan*/  hlist; int /*<<< orphan*/  copy_range; int /*<<< orphan*/  copy_mode; int /*<<< orphan*/  nlbufsiz; int /*<<< orphan*/  flushtimeout; int /*<<< orphan*/  qthreshold; int /*<<< orphan*/  group_num; int /*<<< orphan*/  timer; int /*<<< orphan*/  use; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EEXIST ; 
 int ENOMEM ; 
 struct nfulnl_instance* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFULNL_COPY_PACKET ; 
 int /*<<< orphan*/  NFULNL_COPY_RANGE_MAX ; 
 int /*<<< orphan*/  NFULNL_NLBUFSIZ_DEFAULT ; 
 int /*<<< orphan*/  NFULNL_QTHRESH_DEFAULT ; 
 int /*<<< orphan*/  NFULNL_TIMEOUT_DEFAULT ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ __instance_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t instance_hashfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * instance_table ; 
 int /*<<< orphan*/  instances_lock ; 
 int /*<<< orphan*/  kfree (struct nfulnl_instance*) ; 
 struct nfulnl_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfulnl_timer ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfulnl_instance *
instance_create(u_int16_t group_num, int pid)
{
	struct nfulnl_instance *inst;
	int err;

	write_lock_bh(&instances_lock);
	if (__instance_lookup(group_num)) {
		err = -EEXIST;
		goto out_unlock;
	}

	inst = kzalloc(sizeof(*inst), GFP_ATOMIC);
	if (!inst) {
		err = -ENOMEM;
		goto out_unlock;
	}

	if (!try_module_get(THIS_MODULE)) {
		kfree(inst);
		err = -EAGAIN;
		goto out_unlock;
	}

	INIT_HLIST_NODE(&inst->hlist);
	spin_lock_init(&inst->lock);
	/* needs to be two, since we _put() after creation */
	atomic_set(&inst->use, 2);

	setup_timer(&inst->timer, nfulnl_timer, (unsigned long)inst);

	inst->peer_pid = pid;
	inst->group_num = group_num;

	inst->qthreshold 	= NFULNL_QTHRESH_DEFAULT;
	inst->flushtimeout 	= NFULNL_TIMEOUT_DEFAULT;
	inst->nlbufsiz 		= NFULNL_NLBUFSIZ_DEFAULT;
	inst->copy_mode 	= NFULNL_COPY_PACKET;
	inst->copy_range 	= NFULNL_COPY_RANGE_MAX;

	hlist_add_head(&inst->hlist,
		       &instance_table[instance_hashfn(group_num)]);

	write_unlock_bh(&instances_lock);

	return inst;

out_unlock:
	write_unlock_bh(&instances_lock);
	return ERR_PTR(err);
}