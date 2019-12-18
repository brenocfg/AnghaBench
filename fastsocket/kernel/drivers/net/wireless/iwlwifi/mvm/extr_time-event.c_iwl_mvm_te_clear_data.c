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
struct iwl_mvm_time_event_data {scalar_t__ id; int running; int /*<<< orphan*/ * vif; scalar_t__ uid; int /*<<< orphan*/  list; } ;
struct iwl_mvm {int /*<<< orphan*/  time_event_lock; } ;

/* Variables and functions */
 scalar_t__ TE_MAX ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void iwl_mvm_te_clear_data(struct iwl_mvm *mvm,
			   struct iwl_mvm_time_event_data *te_data)
{
	lockdep_assert_held(&mvm->time_event_lock);

	if (te_data->id == TE_MAX)
		return;

	list_del(&te_data->list);
	te_data->running = false;
	te_data->uid = 0;
	te_data->id = TE_MAX;
	te_data->vif = NULL;
}