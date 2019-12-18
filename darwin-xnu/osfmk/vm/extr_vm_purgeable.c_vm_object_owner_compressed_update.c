#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
typedef  TYPE_2__* task_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_12__ {int phys_footprint; } ;
struct TYPE_11__ {int /*<<< orphan*/  ledger; } ;
struct TYPE_10__ {int purgable; int /*<<< orphan*/  vo_ledger_tag; int /*<<< orphan*/  internal; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_OBJECT_LEDGER_TAG_NONE ; 
 TYPE_2__* VM_OBJECT_OWNER (TYPE_1__*) ; 
#define  VM_PURGABLE_DENY 131 
#define  VM_PURGABLE_EMPTY 130 
#define  VM_PURGABLE_NONVOLATILE 129 
#define  VM_PURGABLE_VOLATILE 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ledger_credit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ledger_debit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ptoa_64 (int) ; 
 TYPE_6__ task_ledgers ; 
 int /*<<< orphan*/  vm_object_ledger_tag_ledgers (TYPE_1__*,int*,int*,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_lock_assert_exclusive (TYPE_1__*) ; 

void
vm_object_owner_compressed_update(
	vm_object_t	object,
	int		delta)
{
	task_t		owner;
	int		ledger_idx_volatile;
	int		ledger_idx_nonvolatile;
	int		ledger_idx_volatile_compressed;
	int		ledger_idx_nonvolatile_compressed;
	boolean_t	do_footprint;

	vm_object_lock_assert_exclusive(object);

	owner = VM_OBJECT_OWNER(object);

	if (delta == 0 ||
	    !object->internal ||
	    (object->purgable == VM_PURGABLE_DENY &&
	     ! object->vo_ledger_tag) ||
	    owner == NULL) {
		/* not an owned purgeable (or tagged) VM object: nothing to update */
		return;
	}
	
	vm_object_ledger_tag_ledgers(object,
				     &ledger_idx_volatile,
				     &ledger_idx_nonvolatile,
				     &ledger_idx_volatile_compressed,
				     &ledger_idx_nonvolatile_compressed,
				     &do_footprint);
	switch (object->purgable) {
	case VM_PURGABLE_DENY:
		/* not purgeable: must be ledger-tagged */
		assert(object->vo_ledger_tag != VM_OBJECT_LEDGER_TAG_NONE);
		/* fallthru */
	case VM_PURGABLE_NONVOLATILE:
		if (delta > 0) {
			ledger_credit(owner->ledger,
				      ledger_idx_nonvolatile_compressed,
				      ptoa_64(delta));
			if (do_footprint) {
				ledger_credit(owner->ledger,
					      task_ledgers.phys_footprint,
					      ptoa_64(delta));
			}
		} else {
			ledger_debit(owner->ledger,
				     ledger_idx_nonvolatile_compressed,
				     ptoa_64(-delta));
			if (do_footprint) {
				ledger_debit(owner->ledger,
					     task_ledgers.phys_footprint,
					     ptoa_64(-delta));
			}
		}
		break;
	case VM_PURGABLE_VOLATILE:
	case VM_PURGABLE_EMPTY:
		if (delta > 0) {
			ledger_credit(owner->ledger,
				      ledger_idx_volatile_compressed,
				      ptoa_64(delta));
		} else {
			ledger_debit(owner->ledger,
				     ledger_idx_volatile_compressed,
				     ptoa_64(-delta));
		}
		break;
	default:
		panic("vm_purgeable_compressed_update(): "
		      "unexpected purgable %d for object %p\n",
		      object->purgable, object);
	}
}