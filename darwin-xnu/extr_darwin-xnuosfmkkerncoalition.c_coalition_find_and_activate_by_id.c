#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  TYPE_1__* coalition_t ;
struct TYPE_8__ {scalar_t__ ref_count; int /*<<< orphan*/  type; int /*<<< orphan*/  id; int /*<<< orphan*/  active_count; scalar_t__ terminated; scalar_t__ reaped; } ;

/* Variables and functions */
 TYPE_1__* COALITION_NULL ; 
 int /*<<< orphan*/  ac ; 
 int /*<<< orphan*/  coal_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coal_type_str (int /*<<< orphan*/ ) ; 
 TYPE_1__* coalition_find_by_id_internal (scalar_t__) ; 
 int /*<<< orphan*/  coalition_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  coalition_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  coalitions_list_lock ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc ; 

coalition_t
coalition_find_and_activate_by_id(uint64_t cid)
{
	if (cid == 0) {
		return COALITION_NULL;
	}

	lck_mtx_lock(&coalitions_list_lock);

	coalition_t coal = coalition_find_by_id_internal(cid);
	if (coal == COALITION_NULL) {
		lck_mtx_unlock(&coalitions_list_lock);
		return COALITION_NULL;
	}

	coalition_lock(coal);

	if (coal->reaped || coal->terminated) {
		/* Too late to put something new into this coalition, it's
		 * already on its way out the door */
		coalition_unlock(coal);
		lck_mtx_unlock(&coalitions_list_lock);
		return COALITION_NULL;
	}

	if (coal->ref_count == 0) {
		panic("resurrecting coalition %p id:%llu type:%s, active_count:%u\n",
				coal, coal->id, coal_type_str(coal->type), coal->active_count);
	}

	coal->ref_count++;
	coal->active_count++;

#if COALITION_DEBUG
	uint32_t rc = coal->ref_count;
	uint32_t ac = coal->active_count;
#endif

	coalition_unlock(coal);
	lck_mtx_unlock(&coalitions_list_lock);

	coal_dbg("id:%llu type:%s ref_count:%u, active_count:%u",
		 coal->id, coal_type_str(coal->type), rc, ac);

	return coal;
}