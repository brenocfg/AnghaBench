#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* coalition_t ;
struct TYPE_7__ {size_t type; int termrequested; scalar_t__ active_count; int ref_count; int /*<<< orphan*/  coalitions; scalar_t__ reaped; int /*<<< orphan*/  terminated; } ;

/* Variables and functions */
 size_t COALITION_TYPE_MAX ; 
 int /*<<< orphan*/  KERN_DEFAULT_SET ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  KERN_TERMINATED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  coalition_count ; 
 int /*<<< orphan*/  coalition_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  coalition_release (TYPE_1__*) ; 
 int /*<<< orphan*/  coalition_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  coalitions_list_lock ; 
 TYPE_1__** init_coalition ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remqueue (int /*<<< orphan*/ *) ; 

kern_return_t
coalition_reap_internal(coalition_t coal)
{
	assert(coal->type <= COALITION_TYPE_MAX);

	if (coal == init_coalition[coal->type]) {
		return KERN_DEFAULT_SET;
	}

	coalition_lock(coal);
	if (coal->reaped) {
		coalition_unlock(coal);
		return KERN_TERMINATED;
	}
	if (!coal->terminated) {
		coalition_unlock(coal);
		return KERN_FAILURE;
	}
	assert(coal->termrequested);
	if (coal->active_count > 0) {
		coalition_unlock(coal);
		return KERN_FAILURE;
	}

	coal->reaped = TRUE;

	/* Caller, launchd, and coalitions list should each have a reference */
	assert(coal->ref_count > 2);

	coalition_unlock(coal);

	lck_mtx_lock(&coalitions_list_lock);
	coalition_count--;
	remqueue(&coal->coalitions);
	lck_mtx_unlock(&coalitions_list_lock);

	/* Release the list's reference and launchd's reference. */
	coalition_release(coal);
	coalition_release(coal);

	return KERN_SUCCESS;
}