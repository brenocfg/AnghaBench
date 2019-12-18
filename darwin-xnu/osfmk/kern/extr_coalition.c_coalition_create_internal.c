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
struct coalition {int type; int role; int ref_count; int should_notify; scalar_t__ id; int /*<<< orphan*/  coalitions; int /*<<< orphan*/  lock; int /*<<< orphan*/  privileged; } ;
typedef  scalar_t__ kern_return_t ;
typedef  struct coalition* coalition_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 struct coalition* COALITION_NULL ; 
 int COALITION_TYPE_MAX ; 
 int /*<<< orphan*/  DBG_MACH_COALITION ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KDBG_RELEASE (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_RESOURCE_SHORTAGE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_COALITION_NEW ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (struct coalition*,int) ; 
 scalar_t__ coal_call (struct coalition*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  coal_dbg (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coal_type_str (int) ; 
 int /*<<< orphan*/  coalition_count ; 
 int /*<<< orphan*/  coalition_next_id ; 
 int /*<<< orphan*/  coalition_zone ; 
 int /*<<< orphan*/  coalitions_lck_attr ; 
 int /*<<< orphan*/  coalitions_lck_grp ; 
 int /*<<< orphan*/  coalitions_list_lock ; 
 int /*<<< orphan*/  coalitions_q ; 
 int /*<<< orphan*/  enqueue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  lck_mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct coalition*) ; 

kern_return_t
coalition_create_internal(int type, int role, boolean_t privileged, coalition_t *out)
{
	kern_return_t kr;
	struct coalition *new_coal;

	if (type < 0 || type > COALITION_TYPE_MAX)
		return KERN_INVALID_ARGUMENT;

	new_coal = (struct coalition *)zalloc(coalition_zone);
	if (new_coal == COALITION_NULL)
		return KERN_RESOURCE_SHORTAGE;
	bzero(new_coal, sizeof(*new_coal));

	new_coal->type = type;
	new_coal->role = role;

	/* initialize type-specific resources */
	kr = coal_call(new_coal, init, privileged);
	if (kr != KERN_SUCCESS) {
		zfree(coalition_zone, new_coal);
		return kr;
	}

	/* One for caller, one for coalitions list */
	new_coal->ref_count = 2;

	new_coal->privileged = privileged ? TRUE : FALSE;
#if DEVELOPMENT || DEBUG
	new_coal->should_notify = 1;
#endif

	lck_mtx_init(&new_coal->lock, &coalitions_lck_grp, &coalitions_lck_attr);

	lck_mtx_lock(&coalitions_list_lock);
	new_coal->id = coalition_next_id++;
	coalition_count++;
	enqueue_tail(&coalitions_q, &new_coal->coalitions);

	KDBG_RELEASE(MACHDBG_CODE(DBG_MACH_COALITION, MACH_COALITION_NEW),
		new_coal->id, new_coal->type);
	lck_mtx_unlock(&coalitions_list_lock);

	coal_dbg("id:%llu, type:%s", new_coal->id, coal_type_str(new_coal->type));

	*out = new_coal;
	return KERN_SUCCESS;
}