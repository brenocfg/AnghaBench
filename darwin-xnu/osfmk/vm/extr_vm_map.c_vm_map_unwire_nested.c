#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  scalar_t__ vm_map_offset_t ;
typedef  struct vm_map_entry* vm_map_entry_t ;
struct vm_map_entry {scalar_t__ vme_start; int in_transition; scalar_t__ vme_end; scalar_t__ wired_count; scalar_t__ user_wired_count; int needs_wakeup; struct vm_map_entry* vme_next; void* zero_wired_pages; scalar_t__ use_pmap; scalar_t__ is_sub_map; scalar_t__ superpage_size; } ;
typedef  int /*<<< orphan*/ * pmap_t ;
typedef  void* kern_return_t ;
typedef  void* boolean_t ;
struct TYPE_16__ {unsigned int timestamp; int /*<<< orphan*/ * pmap; } ;

/* Variables and functions */
 void* FALSE ; 
 void* KERN_INVALID_ADDRESS ; 
 void* KERN_SUCCESS ; 
 void* TRUE ; 
 scalar_t__ VME_OFFSET (struct vm_map_entry*) ; 
 TYPE_1__* VME_SUBMAP (struct vm_map_entry*) ; 
 int VM_MAP_PAGE_ALIGNED (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_PAGE_MASK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_MAP_RANGE_CHECK (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int page_aligned (scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  subtract_wire_counts (TYPE_1__*,struct vm_map_entry*,void*) ; 
 int /*<<< orphan*/  vm_fault_unwire (TYPE_1__*,struct vm_map_entry*,void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_end (TYPE_1__*,struct vm_map_entry*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_start (TYPE_1__*,struct vm_map_entry*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_entry_wakeup (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_1__*) ; 
 scalar_t__ vm_map_lookup_entry (TYPE_1__*,scalar_t__,struct vm_map_entry**) ; 
 int /*<<< orphan*/  vm_map_simplify_range (TYPE_1__*,scalar_t__,scalar_t__) ; 
 struct vm_map_entry* vm_map_to_entry (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_1__*) ; 

__attribute__((used)) static kern_return_t
vm_map_unwire_nested(
	vm_map_t		map,
	vm_map_offset_t		start,
	vm_map_offset_t		end,
	boolean_t		user_wire,
	pmap_t			map_pmap,
	vm_map_offset_t		pmap_addr)
{
	vm_map_entry_t		entry;
	struct vm_map_entry	*first_entry, tmp_entry;
	boolean_t		need_wakeup;
	boolean_t		main_map = FALSE;
	unsigned int		last_timestamp;

	vm_map_lock(map);
	if(map_pmap == NULL)
		main_map = TRUE;
	last_timestamp = map->timestamp;

	VM_MAP_RANGE_CHECK(map, start, end);
	assert(page_aligned(start));
	assert(page_aligned(end));
	assert(VM_MAP_PAGE_ALIGNED(start, VM_MAP_PAGE_MASK(map)));
	assert(VM_MAP_PAGE_ALIGNED(end, VM_MAP_PAGE_MASK(map)));

	if (start == end) {
		/* We unwired what the caller asked for: zero pages */
		vm_map_unlock(map);
		return KERN_SUCCESS;
	}

	if (vm_map_lookup_entry(map, start, &first_entry)) {
		entry = first_entry;
		/*
		 * vm_map_clip_start will be done later.
		 * We don't want to unnest any nested sub maps here !
		 */
	}
	else {
		if (!user_wire) {
			panic("vm_map_unwire: start not found");
		}
		/*	Start address is not in map. */
		vm_map_unlock(map);
		return(KERN_INVALID_ADDRESS);
	}

	if (entry->superpage_size) {
		/* superpages are always wired */
		vm_map_unlock(map);
		return KERN_INVALID_ADDRESS;
	}

	need_wakeup = FALSE;
	while ((entry != vm_map_to_entry(map)) && (entry->vme_start < end)) {
		if (entry->in_transition) {
			/*
			 * 1)
			 * Another thread is wiring down this entry. Note
			 * that if it is not for the other thread we would
			 * be unwiring an unwired entry.  This is not
			 * permitted.  If we wait, we will be unwiring memory
			 * we did not wire.
			 *
			 * 2)
			 * Another thread is unwiring this entry.  We did not
			 * have a reference to it, because if we did, this
			 * entry will not be getting unwired now.
			 */
			if (!user_wire) {
				/*
				 * XXX FBDP
				 * This could happen:  there could be some
				 * overlapping vslock/vsunlock operations
				 * going on.
				 * We should probably just wait and retry,
				 * but then we have to be careful that this
				 * entry could get "simplified" after
				 * "in_transition" gets unset and before
				 * we re-lookup the entry, so we would
				 * have to re-clip the entry to avoid
				 * re-unwiring what we have already unwired...
				 * See vm_map_wire_nested().
				 *
				 * Or we could just ignore "in_transition"
				 * here and proceed to decement the wired
				 * count(s) on this entry.  That should be fine
				 * as long as "wired_count" doesn't drop all
				 * the way to 0 (and we should panic if THAT
				 * happens).
				 */
				panic("vm_map_unwire: in_transition entry");
			}

			entry = entry->vme_next;
			continue;
		}

		if (entry->is_sub_map) {
			vm_map_offset_t	sub_start;
			vm_map_offset_t	sub_end;
			vm_map_offset_t	local_end;
			pmap_t		pmap;

			vm_map_clip_start(map, entry, start);
			vm_map_clip_end(map, entry, end);

			sub_start = VME_OFFSET(entry);
			sub_end = entry->vme_end - entry->vme_start;
			sub_end += VME_OFFSET(entry);
			local_end = entry->vme_end;
			if(map_pmap == NULL) {
				if(entry->use_pmap) {
					pmap = VME_SUBMAP(entry)->pmap;
					pmap_addr = sub_start;
				} else {
					pmap = map->pmap;
					pmap_addr = start;
				}
				if (entry->wired_count == 0 ||
				    (user_wire && entry->user_wired_count == 0)) {
					if (!user_wire)
						panic("vm_map_unwire: entry is unwired");
					entry = entry->vme_next;
					continue;
				}

				/*
				 * Check for holes
				 * Holes: Next entry should be contiguous unless
				 * this is the end of the region.
				 */
				if (((entry->vme_end < end) &&
				     ((entry->vme_next == vm_map_to_entry(map)) ||
				      (entry->vme_next->vme_start
				       > entry->vme_end)))) {
					if (!user_wire)
						panic("vm_map_unwire: non-contiguous region");
/*
					entry = entry->vme_next;
					continue;
*/
				}

				subtract_wire_counts(map, entry, user_wire);

				if (entry->wired_count != 0) {
					entry = entry->vme_next;
					continue;
				}

				entry->in_transition = TRUE;
				tmp_entry = *entry;/* see comment in vm_map_wire() */

				/*
				 * We can unlock the map now. The in_transition state
				 * guarantees existance of the entry.
				 */
				vm_map_unlock(map);
				vm_map_unwire_nested(VME_SUBMAP(entry),
						     sub_start, sub_end, user_wire, pmap, pmap_addr);
				vm_map_lock(map);

				if (last_timestamp+1 != map->timestamp) {
					/*
					 * Find the entry again.  It could have been
					 * clipped or deleted after we unlocked the map.
					 */
					if (!vm_map_lookup_entry(map,
								 tmp_entry.vme_start,
								 &first_entry)) {
						if (!user_wire)
							panic("vm_map_unwire: re-lookup failed");
						entry = first_entry->vme_next;
					} else
						entry = first_entry;
				}
				last_timestamp = map->timestamp;

				/*
				 * clear transition bit for all constituent entries
				 * that were in the original entry (saved in
				 * tmp_entry).  Also check for waiters.
				 */
				while ((entry != vm_map_to_entry(map)) &&
				       (entry->vme_start < tmp_entry.vme_end)) {
					assert(entry->in_transition);
					entry->in_transition = FALSE;
					if (entry->needs_wakeup) {
						entry->needs_wakeup = FALSE;
						need_wakeup = TRUE;
					}
					entry = entry->vme_next;
				}
				continue;
			} else {
				vm_map_unlock(map);
				vm_map_unwire_nested(VME_SUBMAP(entry),
						     sub_start, sub_end, user_wire, map_pmap,
						     pmap_addr);
				vm_map_lock(map);

				if (last_timestamp+1 != map->timestamp) {
					/*
					 * Find the entry again.  It could have been
					 * clipped or deleted after we unlocked the map.
					 */
					if (!vm_map_lookup_entry(map,
								 tmp_entry.vme_start,
								 &first_entry)) {
						if (!user_wire)
							panic("vm_map_unwire: re-lookup failed");
						entry = first_entry->vme_next;
					} else
						entry = first_entry;
				}
				last_timestamp = map->timestamp;
			}
		}


		if ((entry->wired_count == 0) ||
		    (user_wire && entry->user_wired_count == 0)) {
			if (!user_wire)
				panic("vm_map_unwire: entry is unwired");

			entry = entry->vme_next;
			continue;
		}

		assert(entry->wired_count > 0 &&
		       (!user_wire || entry->user_wired_count > 0));

		vm_map_clip_start(map, entry, start);
		vm_map_clip_end(map, entry, end);

		/*
		 * Check for holes
		 * Holes: Next entry should be contiguous unless
		 *	  this is the end of the region.
		 */
		if (((entry->vme_end < end) &&
		     ((entry->vme_next == vm_map_to_entry(map)) ||
		      (entry->vme_next->vme_start > entry->vme_end)))) {

			if (!user_wire)
				panic("vm_map_unwire: non-contiguous region");
			entry = entry->vme_next;
			continue;
		}

		subtract_wire_counts(map, entry, user_wire);

		if (entry->wired_count != 0) {
			entry = entry->vme_next;
			continue;
		}

		if(entry->zero_wired_pages) {
			entry->zero_wired_pages = FALSE;
		}

		entry->in_transition = TRUE;
		tmp_entry = *entry;	/* see comment in vm_map_wire() */

		/*
		 * We can unlock the map now. The in_transition state
		 * guarantees existance of the entry.
		 */
		vm_map_unlock(map);
		if(map_pmap) {
			vm_fault_unwire(map,
					&tmp_entry, FALSE, map_pmap, pmap_addr);
		} else {
			vm_fault_unwire(map,
					&tmp_entry, FALSE, map->pmap,
					tmp_entry.vme_start);
		}
		vm_map_lock(map);

		if (last_timestamp+1 != map->timestamp) {
			/*
			 * Find the entry again.  It could have been clipped
			 * or deleted after we unlocked the map.
			 */
			if (!vm_map_lookup_entry(map, tmp_entry.vme_start,
						 &first_entry)) {
				if (!user_wire)
					panic("vm_map_unwire: re-lookup failed");
				entry = first_entry->vme_next;
			} else
				entry = first_entry;
		}
		last_timestamp = map->timestamp;

		/*
		 * clear transition bit for all constituent entries that
		 * were in the original entry (saved in tmp_entry).  Also
		 * check for waiters.
		 */
		while ((entry != vm_map_to_entry(map)) &&
		       (entry->vme_start < tmp_entry.vme_end)) {
			assert(entry->in_transition);
			entry->in_transition = FALSE;
			if (entry->needs_wakeup) {
				entry->needs_wakeup = FALSE;
				need_wakeup = TRUE;
			}
			entry = entry->vme_next;
		}
	}

	/*
	 * We might have fragmented the address space when we wired this
	 * range of addresses.  Attempt to re-coalesce these VM map entries
	 * with their neighbors now that they're no longer wired.
	 * Under some circumstances, address space fragmentation can
	 * prevent VM object shadow chain collapsing, which can cause
	 * swap space leaks.
	 */
	vm_map_simplify_range(map, start, end);

	vm_map_unlock(map);
	/*
	 * wake up anybody waiting on entries that we have unwired.
	 */
	if (need_wakeup)
		vm_map_entry_wakeup(map);
	return(KERN_SUCCESS);

}