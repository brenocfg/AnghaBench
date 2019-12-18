#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  TYPE_2__* proc_t ;
struct TYPE_12__ {unsigned int entry_count; int /*<<< orphan*/  js_gencount; TYPE_4__* entries; } ;
typedef  TYPE_3__ memorystatus_jetsam_snapshot_t ;
struct TYPE_13__ {scalar_t__ pid; scalar_t__ priority; scalar_t__ jse_killtime; scalar_t__ killed; scalar_t__ jse_memory_region_count; scalar_t__ jse_page_table_pages; scalar_t__ jse_iokit_mapped_pages; scalar_t__ jse_alternate_accounting_compressed_pages; scalar_t__ jse_alternate_accounting_pages; scalar_t__ jse_purgeable_nonvolatile_compressed_pages; scalar_t__ jse_purgeable_nonvolatile_pages; scalar_t__ jse_internal_compressed_pages; scalar_t__ jse_internal_pages; scalar_t__ purgeable_pages; scalar_t__ max_pages_lifetime; scalar_t__ pages; int /*<<< orphan*/  fds; int /*<<< orphan*/  user_data; int /*<<< orphan*/  state; int /*<<< orphan*/  name; scalar_t__ jse_thaw_count; int /*<<< orphan*/  jse_idle_delta; int /*<<< orphan*/  jse_gencount; } ;
typedef  TYPE_4__ memorystatus_jetsam_snapshot_entry_t ;
struct TYPE_11__ {scalar_t__ p_pid; scalar_t__ p_memstat_effectivepriority; int /*<<< orphan*/  task; TYPE_1__* p_fd; int /*<<< orphan*/  p_memstat_userdata; int /*<<< orphan*/  p_name; scalar_t__ p_memstat_thaw_count; int /*<<< orphan*/  p_memstat_idle_delta; } ;
struct TYPE_10__ {int /*<<< orphan*/  fd_nfiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int,char*,scalar_t__,scalar_t__,unsigned int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memorystatus_build_state (TYPE_2__*) ; 
 int /*<<< orphan*/  memorystatus_get_task_memory_region_count (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  memorystatus_get_task_page_counts (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memorystatus_get_task_phys_footprint_page_counts (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ memorystatus_init_jetsam_snapshot_entry_locked (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* memorystatus_jetsam_snapshot ; 
 unsigned int memorystatus_jetsam_snapshot_count ; 
 unsigned int memorystatus_jetsam_snapshot_max ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int /*<<< orphan*/  proc_list_mlock ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
memorystatus_update_jetsam_snapshot_entry_locked(proc_t p, uint32_t kill_cause, uint64_t killtime)
{
	memorystatus_jetsam_snapshot_entry_t *entry = NULL;
	memorystatus_jetsam_snapshot_t *snapshot    = NULL;
	memorystatus_jetsam_snapshot_entry_t *snapshot_list = NULL;

	unsigned int i;

	LCK_MTX_ASSERT(proc_list_mlock, LCK_MTX_ASSERT_OWNED);

	if (memorystatus_jetsam_snapshot_count == 0) {
		/*
		 * No active snapshot.
		 * Nothing to do.
		 */
		return;
	}

	/*
	 * Sanity check as this routine should only be called
	 * from a jetsam kill path.
	 */
	assert(kill_cause != 0 && killtime != 0);

	snapshot       = memorystatus_jetsam_snapshot;
	snapshot_list  = memorystatus_jetsam_snapshot->entries;

	for (i = 0; i < memorystatus_jetsam_snapshot_count; i++) {
		if (snapshot_list[i].pid == p->p_pid) {

			entry = &snapshot_list[i];

			if (entry->killed || entry->jse_killtime) {
				/*
				 * We apparently raced on the exit path
				 * for this process, as it's snapshot entry
				 * has already recorded a kill.
				 */
				assert(entry->killed && entry->jse_killtime);
				break;
			}

			/*
			 * Update the entry we just found in the snapshot.
			 */

			entry->killed       = kill_cause;
			entry->jse_killtime = killtime;
			entry->jse_gencount = snapshot->js_gencount;
			entry->jse_idle_delta = p->p_memstat_idle_delta;
#if CONFIG_FREEZE
			entry->jse_thaw_count = p->p_memstat_thaw_count;
#else /* CONFIG_FREEZE */
			entry->jse_thaw_count = 0;
#endif /* CONFIG_FREEZE */

			/*
			 * If a process has moved between bands since snapshot was
			 * initialized, then likely these fields changed too.
			 */
			 if (entry->priority != p->p_memstat_effectivepriority) {

				strlcpy(entry->name, p->p_name, sizeof(entry->name));
				entry->priority  = p->p_memstat_effectivepriority;
				entry->state     = memorystatus_build_state(p);
				entry->user_data = p->p_memstat_userdata;
				entry->fds       = p->p_fd->fd_nfiles;
			 }

			 /*
			  * Always update the page counts on a kill.
			  */

			 uint32_t pages              = 0;
			 uint32_t max_pages_lifetime = 0;
			 uint32_t purgeable_pages    = 0;

			 memorystatus_get_task_page_counts(p->task, &pages, &max_pages_lifetime, &purgeable_pages);
			 entry->pages              = (uint64_t)pages;
			 entry->max_pages_lifetime = (uint64_t)max_pages_lifetime;
			 entry->purgeable_pages    = (uint64_t)purgeable_pages;

			 uint64_t internal_pages			= 0;
			 uint64_t internal_compressed_pages		= 0;
			 uint64_t purgeable_nonvolatile_pages		= 0;
			 uint64_t purgeable_nonvolatile_compressed_pages = 0;
			 uint64_t alternate_accounting_pages		= 0;
			 uint64_t alternate_accounting_compressed_pages = 0;
			 uint64_t iokit_mapped_pages			= 0;
			 uint64_t page_table_pages			= 0;

			 memorystatus_get_task_phys_footprint_page_counts(p->task, &internal_pages, &internal_compressed_pages,
									  &purgeable_nonvolatile_pages, &purgeable_nonvolatile_compressed_pages,
									  &alternate_accounting_pages, &alternate_accounting_compressed_pages,
									  &iokit_mapped_pages, &page_table_pages);

			 entry->jse_internal_pages = internal_pages;
			 entry->jse_internal_compressed_pages = internal_compressed_pages;
			 entry->jse_purgeable_nonvolatile_pages = purgeable_nonvolatile_pages;
			 entry->jse_purgeable_nonvolatile_compressed_pages = purgeable_nonvolatile_compressed_pages;
			 entry->jse_alternate_accounting_pages = alternate_accounting_pages;
			 entry->jse_alternate_accounting_compressed_pages = alternate_accounting_compressed_pages;
			 entry->jse_iokit_mapped_pages = iokit_mapped_pages;
			 entry->jse_page_table_pages = page_table_pages;

			 uint64_t region_count = 0;
			 memorystatus_get_task_memory_region_count(p->task, &region_count);
			 entry->jse_memory_region_count = region_count;

			 goto exit;
		}
	}

	if (entry == NULL) {
		/*
		 * The entry was not found in the snapshot, so the process must have
		 * launched after the snapshot was initialized.
		 * Let's try to append the new entry.
		 */
		if (memorystatus_jetsam_snapshot_count < memorystatus_jetsam_snapshot_max) {
			/*
			 * A populated snapshot buffer exists
			 * and there is room to init a new entry.
			 */
			assert(memorystatus_jetsam_snapshot_count == snapshot->entry_count);

			unsigned int next = memorystatus_jetsam_snapshot_count;

			if(memorystatus_init_jetsam_snapshot_entry_locked(p, &snapshot_list[next], (snapshot->js_gencount)) == TRUE) {

				entry = &snapshot_list[next];
				entry->killed       = kill_cause;
				entry->jse_killtime = killtime;

				snapshot->entry_count = ++next;
				memorystatus_jetsam_snapshot_count = next;

				if (memorystatus_jetsam_snapshot_count >= memorystatus_jetsam_snapshot_max) {
					/*
					 * We just used the last slot in the snapshot buffer.
					 * We only want to log it once... so we do it here
					 * when we notice we've hit the max.
					 */
					printf("memorystatus: WARNING snapshot buffer is full, count %d\n",
					       memorystatus_jetsam_snapshot_count);
				}
			}
		}
	}

exit:
	if (entry == NULL) {
		/*
		 * If we reach here, the snapshot buffer could not be updated.
		 * Most likely, the buffer is full, in which case we would have
		 * logged a warning in the previous call.
		 *
		 * For now, we will stop appending snapshot entries.
		 * When the buffer is consumed, the snapshot state will reset.
		 */

		MEMORYSTATUS_DEBUG(4, "memorystatus_update_jetsam_snapshot_entry_locked: failed to update pid %d, priority %d, count %d\n",
				   p->p_pid, p->p_memstat_effectivepriority,  memorystatus_jetsam_snapshot_count);
	}

	return;
}