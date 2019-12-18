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
typedef  void* u32 ;
struct qdisc_size_table {scalar_t__ parent; int flags; int padded; struct qdisc_size_table* stab; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; void* handle; } ;
struct nlattr {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct Qdisc_ops {int (* init ) (struct qdisc_size_table*,struct nlattr*) ;int /*<<< orphan*/  (* destroy ) (struct qdisc_size_table*) ;int /*<<< orphan*/  owner; } ;
struct Qdisc {scalar_t__ parent; int flags; int padded; struct Qdisc* stab; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; void* handle; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int IFNAMSIZ ; 
 scalar_t__ IS_ERR (struct qdisc_size_table*) ; 
 int PTR_ERR (struct qdisc_size_table*) ; 
 size_t TCA_KIND ; 
 size_t TCA_OPTIONS ; 
 size_t TCA_RATE ; 
 size_t TCA_STAB ; 
 int TCQ_F_INGRESS ; 
 int TCQ_F_MQROOT ; 
 void* TC_H_INGRESS ; 
 void* TC_H_MAKE (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ TC_H_ROOT ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int gen_new_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct nlattr*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int nla_strlcpy (char*,struct nlattr*,int) ; 
 struct qdisc_size_table* qdisc_alloc (struct netdev_queue*,struct Qdisc_ops*) ; 
 void* qdisc_alloc_handle (struct net_device*) ; 
 struct qdisc_size_table* qdisc_get_stab (struct nlattr*) ; 
 int /*<<< orphan*/  qdisc_list_add (struct qdisc_size_table*) ; 
 int /*<<< orphan*/ * qdisc_lock (struct qdisc_size_table*) ; 
 struct Qdisc_ops* qdisc_lookup_ops (struct nlattr*) ; 
 int /*<<< orphan*/  qdisc_put_stab (struct qdisc_size_table*) ; 
 int /*<<< orphan*/ * qdisc_root_sleeping_lock (struct qdisc_size_table*) ; 
 int /*<<< orphan*/  qdisc_rx_lock ; 
 int /*<<< orphan*/  qdisc_tx_lock ; 
 int /*<<< orphan*/  request_module (char*,char*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int stub1 (struct qdisc_size_table*,struct nlattr*) ; 
 int /*<<< orphan*/  stub2 (struct qdisc_size_table*) ; 

__attribute__((used)) static struct Qdisc *
qdisc_create(struct net_device *dev, struct netdev_queue *dev_queue,
	     struct Qdisc *p, u32 parent, u32 handle,
	     struct nlattr **tca, int *errp)
{
	int err;
	struct nlattr *kind = tca[TCA_KIND];
	struct Qdisc *sch;
	struct Qdisc_ops *ops;
	struct qdisc_size_table *stab;

	ops = qdisc_lookup_ops(kind);
#ifdef CONFIG_MODULES
	if (ops == NULL && kind != NULL) {
		char name[IFNAMSIZ];
		if (nla_strlcpy(name, kind, IFNAMSIZ) < IFNAMSIZ) {
			/* We dropped the RTNL semaphore in order to
			 * perform the module load.  So, even if we
			 * succeeded in loading the module we have to
			 * tell the caller to replay the request.  We
			 * indicate this using -EAGAIN.
			 * We replay the request because the device may
			 * go away in the mean time.
			 */
			rtnl_unlock();
			request_module("sch_%s", name);
			rtnl_lock();
			ops = qdisc_lookup_ops(kind);
			if (ops != NULL) {
				/* We will try again qdisc_lookup_ops,
				 * so don't keep a reference.
				 */
				module_put(ops->owner);
				err = -EAGAIN;
				goto err_out;
			}
		}
	}
#endif

	err = -ENOENT;
	if (ops == NULL)
		goto err_out;

	sch = qdisc_alloc(dev_queue, ops);
	if (IS_ERR(sch)) {
		err = PTR_ERR(sch);
		goto err_out2;
	}

	sch->parent = parent;

	if (handle == TC_H_INGRESS) {
		sch->flags |= TCQ_F_INGRESS;
		handle = TC_H_MAKE(TC_H_INGRESS, 0);
		lockdep_set_class(qdisc_lock(sch), &qdisc_rx_lock);
	} else {
		if (handle == 0) {
			handle = qdisc_alloc_handle(dev);
			err = -ENOMEM;
			if (handle == 0)
				goto err_out3;
		}
		lockdep_set_class(qdisc_lock(sch), &qdisc_tx_lock);
	}

	sch->handle = handle;

	if (!ops->init || (err = ops->init(sch, tca[TCA_OPTIONS])) == 0) {
		if (tca[TCA_STAB]) {
			stab = qdisc_get_stab(tca[TCA_STAB]);
			if (IS_ERR(stab)) {
				err = PTR_ERR(stab);
				goto err_out4;
			}
			sch->stab = stab;
		}
		if (tca[TCA_RATE]) {
			spinlock_t *root_lock;

			err = -EOPNOTSUPP;
			if (sch->flags & TCQ_F_MQROOT)
				goto err_out4;

			if ((sch->parent != TC_H_ROOT) &&
			    !(sch->flags & TCQ_F_INGRESS) &&
			    (!p || !(p->flags & TCQ_F_MQROOT)))
				root_lock = qdisc_root_sleeping_lock(sch);
			else
				root_lock = qdisc_lock(sch);

			err = gen_new_estimator(&sch->bstats, &sch->rate_est,
						root_lock, tca[TCA_RATE]);
			if (err)
				goto err_out4;
		}

		qdisc_list_add(sch);

		return sch;
	}
err_out3:
	dev_put(dev);
	kfree((char *) sch - sch->padded);
err_out2:
	module_put(ops->owner);
err_out:
	*errp = err;
	return NULL;

err_out4:
	/*
	 * Any broken qdiscs that would require a ops->reset() here?
	 * The qdisc was never in action so it shouldn't be necessary.
	 */
	qdisc_put_stab(sch->stab);
	if (ops->destroy)
		ops->destroy(sch);
	goto err_out3;
}