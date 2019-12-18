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
struct ppp_net {int /*<<< orphan*/  all_ppp_mutex; int /*<<< orphan*/  units_idr; } ;
struct TYPE_2__ {int dead; int /*<<< orphan*/  rwait; int /*<<< orphan*/  index; } ;
struct ppp {int closing; TYPE_1__ file; int /*<<< orphan*/ * owner; int /*<<< orphan*/  dev; int /*<<< orphan*/  ppp_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppp_lock (struct ppp*) ; 
 struct ppp_net* ppp_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppp_unlock (struct ppp*) ; 
 int /*<<< orphan*/  unit_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ppp_shutdown_interface(struct ppp *ppp)
{
	struct ppp_net *pn;

	pn = ppp_pernet(ppp->ppp_net);
	mutex_lock(&pn->all_ppp_mutex);

	/* This will call dev_close() for us. */
	ppp_lock(ppp);
	if (!ppp->closing) {
		ppp->closing = 1;
		ppp_unlock(ppp);
		unregister_netdev(ppp->dev);
	} else
		ppp_unlock(ppp);

	unit_put(&pn->units_idr, ppp->file.index);
	ppp->file.dead = 1;
	ppp->owner = NULL;
	wake_up_interruptible(&ppp->file.rwait);

	mutex_unlock(&pn->all_ppp_mutex);
}