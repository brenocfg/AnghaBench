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
struct svc_xprt {int /*<<< orphan*/  xpt_flags; int /*<<< orphan*/  xpt_ready; int /*<<< orphan*/  xpt_list; TYPE_1__* xpt_ops; struct svc_serv* xpt_server; } ;
struct svc_serv {int /*<<< orphan*/  sv_lock; int /*<<< orphan*/  sv_tmpcnt; } ;
struct svc_deferred_req {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* xpo_detach ) (struct svc_xprt*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  XPT_DEAD ; 
 int /*<<< orphan*/  XPT_DETACHED ; 
 int /*<<< orphan*/  XPT_TEMP ; 
 int /*<<< orphan*/  call_xpt_users (struct svc_xprt*) ; 
 int /*<<< orphan*/  dprintk (char*,struct svc_xprt*) ; 
 int /*<<< orphan*/  kfree (struct svc_deferred_req*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct svc_xprt*) ; 
 struct svc_deferred_req* svc_deferred_dequeue (struct svc_xprt*) ; 
 int /*<<< orphan*/  svc_xprt_put (struct svc_xprt*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void svc_delete_xprt(struct svc_xprt *xprt)
{
	struct svc_serv	*serv = xprt->xpt_server;
	struct svc_deferred_req *dr;

	/* Only do this once */
	if (test_and_set_bit(XPT_DEAD, &xprt->xpt_flags))
		BUG();

	dprintk("svc: svc_delete_xprt(%p)\n", xprt);
	xprt->xpt_ops->xpo_detach(xprt);

	spin_lock_bh(&serv->sv_lock);
	if (!test_and_set_bit(XPT_DETACHED, &xprt->xpt_flags))
		list_del_init(&xprt->xpt_list);
	BUG_ON(!list_empty(&xprt->xpt_ready));
	if (test_bit(XPT_TEMP, &xprt->xpt_flags))
		serv->sv_tmpcnt--;
	spin_unlock_bh(&serv->sv_lock);

	while ((dr = svc_deferred_dequeue(xprt)) != NULL)
		kfree(dr);

	call_xpt_users(xprt);
	svc_xprt_put(xprt);
}