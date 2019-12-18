#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_14__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_page_packed_t ;
struct TYPE_33__ {int /*<<< orphan*/  cur_count; int /*<<< orphan*/  page_list; } ;
typedef  TYPE_3__ vm_page_bucket_t ;
typedef  TYPE_4__* vm_object_t ;
typedef  scalar_t__ vm_object_offset_t ;
typedef  TYPE_5__* task_t ;
typedef  int /*<<< orphan*/  lck_spin_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_36__ {scalar_t__ reusable_count; int /*<<< orphan*/  reused_remove; } ;
struct TYPE_35__ {int /*<<< orphan*/  ledger; } ;
struct TYPE_31__ {scalar_t__ prev; scalar_t__ next; } ;
struct TYPE_34__ {scalar_t__ resident_page_count; scalar_t__ wired_page_count; scalar_t__ reusable_page_count; scalar_t__ purgable; scalar_t__ set_cache_attr; int /*<<< orphan*/  vo_ledger_tag; scalar_t__ all_reusable; int /*<<< orphan*/  wire_tag; TYPE_1__ cached_list; scalar_t__ internal; } ;
struct TYPE_32__ {int vmp_tabled; scalar_t__ vmp_wire_count; scalar_t__ vmp_offset; scalar_t__ vmp_object; void* vmp_reusable; scalar_t__ vmp_xpmapped; int /*<<< orphan*/  vmp_next_m; void* vmp_hashed; int /*<<< orphan*/  vmp_laundry; int /*<<< orphan*/  vmp_cleaning; } ;
struct TYPE_30__ {int phys_footprint; } ;

/* Variables and functions */
 int BUCKETS_PER_LOCK ; 
 void* FALSE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  OSAddAtomic (int,scalar_t__*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_5__* TASK_NULL ; 
 scalar_t__ TRUE ; 
 TYPE_5__* VM_OBJECT_OWNER (TYPE_4__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WIRED_PAGE_REMOVE (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WIRED_PAGE_UPDATE_END (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WIRED_PAGE_UPDATE_START (TYPE_4__*) ; 
 int /*<<< orphan*/  VM_PAGE_CHECK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_PAGE_GET_PHYS_PAGE (TYPE_2__*) ; 
 TYPE_4__* VM_PAGE_OBJECT (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_PAGE_PACK_PTR (int /*<<< orphan*/ *) ; 
 scalar_t__ VM_PAGE_PAGEABLE (TYPE_2__*) ; 
 scalar_t__ VM_PAGE_UNPACK_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ VM_PAGE_WIRED (TYPE_2__*) ; 
 scalar_t__ VM_PURGABLE_DENY ; 
 scalar_t__ VM_PURGABLE_EMPTY ; 
 scalar_t__ VM_PURGABLE_NONVOLATILE ; 
 scalar_t__ VM_PURGABLE_VOLATILE ; 
 int /*<<< orphan*/  XPR (int /*<<< orphan*/ ,char*,TYPE_4__*,scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPR_VM_PAGE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lck_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ledger_debit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_set_cache_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_14__ task_ledgers ; 
 int /*<<< orphan*/  vm_object_cache_remove (TYPE_4__*) ; 
 int /*<<< orphan*/  vm_object_ledger_tag_ledgers (TYPE_4__*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  vm_object_lock_assert_exclusive (TYPE_4__*) ; 
 int /*<<< orphan*/ * vm_page_bucket_locks ; 
 TYPE_3__* vm_page_buckets ; 
 scalar_t__ vm_page_external_count ; 
 int vm_page_hash (TYPE_4__*,scalar_t__) ; 
 scalar_t__ vm_page_internal_count ; 
 scalar_t__ vm_page_purgeable_count ; 
 scalar_t__ vm_page_purgeable_wired_count ; 
 int /*<<< orphan*/  vm_page_queue_lock ; 
 int /*<<< orphan*/  vm_page_remove_internal (TYPE_2__*) ; 
 TYPE_6__ vm_page_stats_reusable ; 
 scalar_t__ vm_page_xpmapped_external_count ; 

void
vm_page_remove(
	vm_page_t	mem,
	boolean_t	remove_from_hash)
{
	vm_page_bucket_t *bucket;
	vm_page_t	this;
	lck_spin_t	*bucket_lock;
	int		hash_id;
	task_t		owner;
	vm_object_t	m_object;
	int		ledger_idx_volatile;
	int		ledger_idx_nonvolatile;
	int		ledger_idx_volatile_compressed;
	int		ledger_idx_nonvolatile_compressed;
	int		do_footprint;

	m_object = VM_PAGE_OBJECT(mem);

        XPR(XPR_VM_PAGE,
                "vm_page_remove, object 0x%X offset 0x%X page 0x%X\n",
                m_object, mem->vmp_offset, 
		mem, 0,0);

	vm_object_lock_assert_exclusive(m_object);
	assert(mem->vmp_tabled);
	assert(!mem->vmp_cleaning);
	assert(!mem->vmp_laundry);

	if (VM_PAGE_PAGEABLE(mem)) {
		LCK_MTX_ASSERT(&vm_page_queue_lock, LCK_MTX_ASSERT_OWNED);
	}
#if 0
	/*
	 * we don't hold the page queue lock
	 * so this check isn't safe to make
	 */
	VM_PAGE_CHECK(mem);
#endif
	if (remove_from_hash == TRUE) {
		/*
		 *	Remove from the object_object/offset hash table
		 */
		hash_id = vm_page_hash(m_object, mem->vmp_offset);
		bucket = &vm_page_buckets[hash_id];
		bucket_lock = &vm_page_bucket_locks[hash_id / BUCKETS_PER_LOCK];

		lck_spin_lock(bucket_lock);

		if ((this = (vm_page_t)(VM_PAGE_UNPACK_PTR(bucket->page_list))) == mem) {
			/* optimize for common case */

			bucket->page_list = mem->vmp_next_m;
		} else {
			vm_page_packed_t	*prev;

			for (prev = &this->vmp_next_m;
			     (this = (vm_page_t)(VM_PAGE_UNPACK_PTR(*prev))) != mem;
			     prev = &this->vmp_next_m)
				continue;
			*prev = this->vmp_next_m;
		}
#if     MACH_PAGE_HASH_STATS
		bucket->cur_count--;
#endif /* MACH_PAGE_HASH_STATS */
		mem->vmp_hashed = FALSE;
		this->vmp_next_m = VM_PAGE_PACK_PTR(NULL);
		lck_spin_unlock(bucket_lock);
	}
	/*
	 *	Now remove from the object's list of backed pages.
	 */

	vm_page_remove_internal(mem);

	/*
	 *	And show that the object has one fewer resident
	 *	page.
	 */

	assert(m_object->resident_page_count > 0);
	m_object->resident_page_count--;

	if (m_object->internal) {
#if DEBUG
		assert(vm_page_internal_count);
#endif /* DEBUG */

		OSAddAtomic(-1, &vm_page_internal_count);
	} else {
		assert(vm_page_external_count);
		OSAddAtomic(-1, &vm_page_external_count);

		if (mem->vmp_xpmapped) {
			assert(vm_page_xpmapped_external_count);
			OSAddAtomic(-1, &vm_page_xpmapped_external_count);
		}
	}
	if (!m_object->internal &&
	    m_object->cached_list.next &&
	    m_object->cached_list.prev) {
		if (m_object->resident_page_count == 0)
			vm_object_cache_remove(m_object);
	}

	if (VM_PAGE_WIRED(mem)) {
		assert(mem->vmp_wire_count > 0);
		VM_OBJECT_WIRED_PAGE_UPDATE_START(m_object);
		VM_OBJECT_WIRED_PAGE_REMOVE(m_object, mem);
		VM_OBJECT_WIRED_PAGE_UPDATE_END(m_object, m_object->wire_tag);
	}
	assert(m_object->resident_page_count >=
	       m_object->wired_page_count);
	if (mem->vmp_reusable) {
		assert(m_object->reusable_page_count > 0);
		m_object->reusable_page_count--;
		assert(m_object->reusable_page_count <=
		       m_object->resident_page_count);
		mem->vmp_reusable = FALSE;
		OSAddAtomic(-1, &vm_page_stats_reusable.reusable_count);
		vm_page_stats_reusable.reused_remove++;
	} else if (m_object->all_reusable) {
		OSAddAtomic(-1, &vm_page_stats_reusable.reusable_count);
		vm_page_stats_reusable.reused_remove++;
	}

	if (m_object->purgable == VM_PURGABLE_DENY &&
	    ! m_object->vo_ledger_tag) {
		owner = TASK_NULL;
	} else {
		owner = VM_OBJECT_OWNER(m_object);
		vm_object_ledger_tag_ledgers(m_object,
					     &ledger_idx_volatile,
					     &ledger_idx_nonvolatile,
					     &ledger_idx_volatile_compressed,
					     &ledger_idx_nonvolatile_compressed,
					     &do_footprint);
	}
	if (owner &&
	    (m_object->purgable == VM_PURGABLE_NONVOLATILE ||
	     m_object->purgable == VM_PURGABLE_DENY ||
	     VM_PAGE_WIRED(mem))) {
		/* less non-volatile bytes */
		ledger_debit(owner->ledger,
			     ledger_idx_nonvolatile,
			     PAGE_SIZE);
		if (do_footprint) {
			/* less footprint */
			ledger_debit(owner->ledger,
				     task_ledgers.phys_footprint,
				     PAGE_SIZE);
		}
	} else if (owner &&
		   (m_object->purgable == VM_PURGABLE_VOLATILE ||
		    m_object->purgable == VM_PURGABLE_EMPTY)) {
		assert(! VM_PAGE_WIRED(mem));
		/* less volatile bytes */
		ledger_debit(owner->ledger,
			     ledger_idx_volatile,
			     PAGE_SIZE);
	}
	if (m_object->purgable == VM_PURGABLE_VOLATILE) {
		if (VM_PAGE_WIRED(mem)) {
			assert(vm_page_purgeable_wired_count > 0);
			OSAddAtomic(-1, &vm_page_purgeable_wired_count);
		} else {
			assert(vm_page_purgeable_count > 0);
			OSAddAtomic(-1, &vm_page_purgeable_count);
		}
	}

	if (m_object->set_cache_attr == TRUE)
		pmap_set_cache_attributes(VM_PAGE_GET_PHYS_PAGE(mem), 0);

	mem->vmp_tabled = FALSE;
	mem->vmp_object = 0;
	mem->vmp_offset = (vm_object_offset_t) -1;
}