#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct ipc_entry {scalar_t__ ie_object; size_t ie_next; int /*<<< orphan*/  ie_request; int /*<<< orphan*/  ie_bits; } ;
typedef  size_t mach_port_index_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* ipc_table_size_t ;
typedef  scalar_t__ ipc_table_index_t ;
typedef  scalar_t__ ipc_table_elems_t ;
typedef  TYPE_2__* ipc_space_t ;
typedef  struct ipc_entry* ipc_entry_t ;
typedef  scalar_t__ ipc_entry_num_t ;
typedef  int /*<<< orphan*/  event_t ;
struct TYPE_15__ {scalar_t__ is_low_mod; scalar_t__ is_high_mod; scalar_t__ is_table_size; int /*<<< orphan*/  is_table_free; TYPE_1__* is_table_next; struct ipc_entry* is_table; } ;
struct TYPE_14__ {scalar_t__ its_size; } ;

/* Variables and functions */
 scalar_t__ IE_BITS_TYPE (int /*<<< orphan*/ ) ; 
 struct ipc_entry* IE_NULL ; 
 scalar_t__ IO_NULL ; 
 scalar_t__ IPC_OBJECT_NULL ; 
 scalar_t__ ITS_SIZE_NONE ; 
 int /*<<< orphan*/  KERN_NO_SPACE ; 
 int /*<<< orphan*/  KERN_RESOURCE_SHORTAGE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ MACH_PORT_TYPE_SEND ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ipc_entry_grow_count ; 
 scalar_t__ ipc_entry_grow_freelist_entries ; 
 scalar_t__ ipc_entry_grow_freelist_entries_max ; 
 int /*<<< orphan*/  ipc_entry_grow_rescan ; 
 int /*<<< orphan*/  ipc_entry_grow_rescan_entries ; 
 size_t ipc_entry_grow_rescan_entries_max ; 
 scalar_t__ ipc_entry_grow_rescan_max ; 
 int /*<<< orphan*/  ipc_hash_table_delete (struct ipc_entry*,scalar_t__,scalar_t__,size_t,struct ipc_entry*) ; 
 int /*<<< orphan*/  ipc_hash_table_insert (struct ipc_entry*,scalar_t__,scalar_t__,size_t,struct ipc_entry*) ; 
 int /*<<< orphan*/  ipc_space_rand_freelist (TYPE_2__*,struct ipc_entry*,scalar_t__,scalar_t__) ; 
 int is_active (TYPE_2__*) ; 
 int /*<<< orphan*/  is_done_growing (TYPE_2__*) ; 
 scalar_t__ is_growing (TYPE_2__*) ; 
 int /*<<< orphan*/  is_start_growing (TYPE_2__*) ; 
 int /*<<< orphan*/  is_write_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  is_write_sleep (TYPE_2__*) ; 
 int /*<<< orphan*/  is_write_unlock (TYPE_2__*) ; 
 struct ipc_entry* it_entries_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  it_entries_free (TYPE_1__*,struct ipc_entry*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 

kern_return_t
ipc_entry_grow_table(
	ipc_space_t		space,
	ipc_table_elems_t	target_size)
{
	ipc_entry_num_t osize, size, nsize, psize;

	ipc_entry_t otable, table;
	ipc_table_size_t oits, its, nits;
	mach_port_index_t i, free_index;
	mach_port_index_t low_mod, hi_mod;
	ipc_table_index_t sanity;
#if IPC_ENTRY_GROW_STATS
	uint64_t rescan_count = 0;
#endif
	assert(is_active(space));

	if (is_growing(space)) {
		/*
		 *	Somebody else is growing the table.
		 *	We just wait for them to finish.
		 */

		is_write_sleep(space);
		return KERN_SUCCESS;
	}

	otable = space->is_table;
		
	its = space->is_table_next;
	size = its->its_size;
		
	/*
	 * Since is_table_next points to the next natural size
	 * we can identify the current size entry.
	 */
	oits = its - 1;
	osize = oits->its_size;
		
	/*
	 * If there is no target size, then the new size is simply
	 * specified by is_table_next.  If there is a target
	 * size, then search for the next entry.
	 */
	if (target_size != ITS_SIZE_NONE) {
		if (target_size <= osize) {
			/* the space is locked */			
			return KERN_SUCCESS;
		}

		psize = osize;
		while ((psize != size) && (target_size > size)) {
			psize = size;
			its++;
			size = its->its_size;
		}
		if (psize == size) {
			is_write_unlock(space);
			return KERN_NO_SPACE;
		}
	}

	if (osize == size) {
		is_write_unlock(space);
		return KERN_NO_SPACE;
	}
 
	nits = its + 1;
	nsize = nits->its_size;
	assert((osize < size) && (size <= nsize));

	/*
	 * We'll attempt to grow the table.
	 *
	 * Because we will be copying without the space lock, reset
	 * the lowest_mod index to just beyond the end of the current
	 * table.  Modification of entries (other than hashes) will
	 * bump this downward, and we only have to reprocess entries
	 * above that mark.  Eventually, we'll get done.
	 */
	is_start_growing(space);
	space->is_low_mod = osize;
	space->is_high_mod = 0;
#if IPC_ENTRY_GROW_STATS
	ipc_entry_grow_count++;
#endif
	is_write_unlock(space);

	table = it_entries_alloc(its);
	if (table == IE_NULL) {
		is_write_lock(space);
		is_done_growing(space);
		is_write_unlock(space);
		thread_wakeup((event_t) space);
		return KERN_RESOURCE_SHORTAGE;
	}

	ipc_space_rand_freelist(space, table, osize, size);

	/* clear out old entries in new table */
	memset((void *)table, 0, osize * sizeof(*table));

	low_mod = 0;
	hi_mod = osize - 1;
 rescan:	
	/*
	 * Within the range of the table that changed, determine what we
	 * have to take action on. For each entry, take a snapshot of the
	 * corresponding entry in the old table (so it won't change
	 * during this iteration). The snapshot may not be self-consistent
	 * (if we caught it in the middle of being changed), so be very
	 * cautious with the values.
	 */
	for (i = low_mod; i <= hi_mod; i++) {
		ipc_entry_t entry = &table[i];
		struct ipc_entry osnap = otable[i]; 

		if (entry->ie_object != osnap.ie_object ||
		    IE_BITS_TYPE(entry->ie_bits) != IE_BITS_TYPE(osnap.ie_bits)) {
			
			if (entry->ie_object != IO_NULL &&
			    IE_BITS_TYPE(entry->ie_bits) == MACH_PORT_TYPE_SEND)
				ipc_hash_table_delete(table, size, entry->ie_object, i, entry);

			entry->ie_object = osnap.ie_object;
			entry->ie_bits = osnap.ie_bits;
			entry->ie_request = osnap.ie_request; /* or ie_next */

			if (entry->ie_object != IO_NULL &&
			    IE_BITS_TYPE(entry->ie_bits) == MACH_PORT_TYPE_SEND)
				ipc_hash_table_insert(table, size, entry->ie_object, i, entry);
		} else {
			assert(entry->ie_object == osnap.ie_object);
			entry->ie_bits = osnap.ie_bits;
			entry->ie_request = osnap.ie_request; /* or ie_next */
		}

	}
	table[0].ie_next = otable[0].ie_next;  /* always rebase the freelist */

	/*
	 * find the end of the freelist (should be short). But be careful,
	 * the list items can change so only follow through truly free entries
	 * (no problem stopping short in those cases, because we'll rescan).
	 */
	free_index = 0;
	for (sanity = 0; sanity < osize; sanity++) {
		if (table[free_index].ie_object != IPC_OBJECT_NULL)
			break;
		i = table[free_index].ie_next;
		if (i == 0 || i >= osize)
			break;
		free_index = i;
	}
#if IPC_ENTRY_GROW_STATS
	ipc_entry_grow_freelist_entries += sanity;
	if (sanity > ipc_entry_grow_freelist_entries_max)
		ipc_entry_grow_freelist_entries_max = sanity;
#endif
		
	is_write_lock(space);

	/*
	 *	We need to do a wakeup on the space,
	 *	to rouse waiting threads.  We defer
	 *	this until the space is unlocked,
	 *	because we don't want them to spin.
	 */

	if (!is_active(space)) {
		/*
		 *	The space died while it was unlocked.
		 */

		is_done_growing(space);
		is_write_unlock(space);
		thread_wakeup((event_t) space);
		it_entries_free(its, table);
		is_write_lock(space);
		return KERN_SUCCESS;
	}

	/* If the space changed while unlocked, go back and process the changes */
	if (space->is_low_mod < osize) {
		assert(space->is_high_mod > 0);
		low_mod = space->is_low_mod;
		space->is_low_mod = osize;
		hi_mod = space->is_high_mod;
		space->is_high_mod = 0;
		is_write_unlock(space);
#if IPC_ENTRY_GROW_STATS
		rescan_count++;
		if (rescan_count > ipc_entry_grow_rescan_max)
			ipc_entry_grow_rescan_max = rescan_count;

		ipc_entry_grow_rescan++;
		ipc_entry_grow_rescan_entries += hi_mod - low_mod + 1;
		if (hi_mod - low_mod + 1 > ipc_entry_grow_rescan_entries_max)
			ipc_entry_grow_rescan_entries_max = hi_mod - low_mod + 1;
#endif
		goto rescan;
	}

	/* link new free entries onto the rest of the freelist */
	assert(table[free_index].ie_next == 0 &&
	       table[free_index].ie_object == IO_NULL);
	table[free_index].ie_next = osize;

	assert(space->is_table == otable);
	assert((space->is_table_next == its) ||
	    (target_size != ITS_SIZE_NONE));
	assert(space->is_table_size == osize);

	space->is_table = table;
	space->is_table_size = size;
	space->is_table_next = nits;
	space->is_table_free += size - osize;

	is_done_growing(space);
	is_write_unlock(space);

	thread_wakeup((event_t) space);

	/*
	 *	Now we need to free the old table.
	 */
	it_entries_free(oits, otable);
	is_write_lock(space);

	return KERN_SUCCESS;
}