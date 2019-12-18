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
struct adapter {scalar_t__* uld_handle; } ;
typedef  enum cxgb4_state { ____Placeholder_cxgb4_state } cxgb4_state ;
struct TYPE_2__ {int /*<<< orphan*/  (* state_change ) (scalar_t__,int) ;} ;

/* Variables and functions */
 unsigned int CXGB4_ULD_MAX ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int) ; 
 int /*<<< orphan*/  uld_mutex ; 
 TYPE_1__* ulds ; 

__attribute__((used)) static void notify_ulds(struct adapter *adap, enum cxgb4_state new_state)
{
	unsigned int i;

	mutex_lock(&uld_mutex);
	for (i = 0; i < CXGB4_ULD_MAX; i++)
		if (adap->uld_handle[i])
			ulds[i].state_change(adap->uld_handle[i], new_state);
	mutex_unlock(&uld_mutex);
}