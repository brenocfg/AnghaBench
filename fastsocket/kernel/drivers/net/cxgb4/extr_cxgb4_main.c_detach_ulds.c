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
struct adapter {int /*<<< orphan*/ ** uld_handle; int /*<<< orphan*/  list_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* state_change ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CXGB4_STATE_DETACH ; 
 unsigned int CXGB4_ULD_MAX ; 
 int /*<<< orphan*/  adapter_list ; 
 int /*<<< orphan*/  cxgb4_netevent_nb ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int netevent_registered ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uld_mutex ; 
 TYPE_1__* ulds ; 
 int /*<<< orphan*/  unregister_netevent_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void detach_ulds(struct adapter *adap)
{
	unsigned int i;

	mutex_lock(&uld_mutex);
	list_del(&adap->list_node);
	for (i = 0; i < CXGB4_ULD_MAX; i++)
		if (adap->uld_handle[i]) {
			ulds[i].state_change(adap->uld_handle[i],
					     CXGB4_STATE_DETACH);
			adap->uld_handle[i] = NULL;
		}
	if (netevent_registered && list_empty(&adapter_list)) {
		unregister_netevent_notifier(&cxgb4_netevent_nb);
		netevent_registered = false;
	}
	mutex_unlock(&uld_mutex);
}