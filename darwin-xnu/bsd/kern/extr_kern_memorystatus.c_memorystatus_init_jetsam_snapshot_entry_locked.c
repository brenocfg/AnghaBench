#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  TYPE_4__* proc_t ;
struct TYPE_12__ {void* tv_usec; void* tv_sec; } ;
struct TYPE_15__ {void* jse_coalition_jetsam_id; scalar_t__ jse_thaw_count; int /*<<< orphan*/  jse_idle_delta; void* jse_gencount; scalar_t__ killed; scalar_t__ jse_killtime; int /*<<< orphan*/  jse_starttime; TYPE_2__ cpu_time; int /*<<< orphan*/  fds; int /*<<< orphan*/ * uuid; int /*<<< orphan*/  user_data; int /*<<< orphan*/  state; void* jse_memory_region_count; void* jse_page_table_pages; void* jse_iokit_mapped_pages; void* jse_alternate_accounting_compressed_pages; void* jse_alternate_accounting_pages; void* jse_purgeable_nonvolatile_compressed_pages; void* jse_purgeable_nonvolatile_pages; void* jse_internal_compressed_pages; void* jse_internal_pages; void* purgeable_pages; void* max_pages_lifetime; void* pages; int /*<<< orphan*/  priority; int /*<<< orphan*/ * name; int /*<<< orphan*/  pid; } ;
typedef  TYPE_5__ memorystatus_jetsam_snapshot_entry_t ;
typedef  void* int64_t ;
typedef  scalar_t__ clock_usec_t ;
typedef  scalar_t__ clock_sec_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_14__ {scalar_t__ p_memstat_thaw_count; int /*<<< orphan*/  p_memstat_idle_delta; TYPE_3__* p_stats; int /*<<< orphan*/  task; TYPE_1__* p_fd; int /*<<< orphan*/ * p_uuid; int /*<<< orphan*/  p_memstat_userdata; int /*<<< orphan*/  p_memstat_effectivepriority; int /*<<< orphan*/  p_name; int /*<<< orphan*/  p_pid; } ;
struct TYPE_13__ {int /*<<< orphan*/  ps_start; } ;
struct TYPE_11__ {int /*<<< orphan*/  fd_nfiles; } ;

/* Variables and functions */
 int COALITION_NUM_TYPES ; 
 size_t COALITION_TYPE_JETSAM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  absolutetime_to_microtime (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_cpu_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memorystatus_build_state (TYPE_4__*) ; 
 int /*<<< orphan*/  memorystatus_get_task_memory_region_count (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  memorystatus_get_task_page_counts (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memorystatus_get_task_phys_footprint_page_counts (int /*<<< orphan*/ ,void**,void**,void**,void**,void**,void**,void**,void**) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_coalitionids (TYPE_4__*,void**) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static boolean_t
memorystatus_init_jetsam_snapshot_entry_locked(proc_t p, memorystatus_jetsam_snapshot_entry_t *entry, uint64_t gencount)
{	
	clock_sec_t                     tv_sec;
	clock_usec_t                    tv_usec;
	uint32_t pages = 0;
	uint32_t max_pages_lifetime = 0;
	uint32_t purgeable_pages = 0;
	uint64_t internal_pages				= 0;
	uint64_t internal_compressed_pages		= 0;
	uint64_t purgeable_nonvolatile_pages		= 0;
	uint64_t purgeable_nonvolatile_compressed_pages	= 0;
	uint64_t alternate_accounting_pages		= 0;
	uint64_t alternate_accounting_compressed_pages	= 0;
	uint64_t iokit_mapped_pages			= 0;
	uint64_t page_table_pages			=0;
	uint64_t region_count				= 0;
	uint64_t cids[COALITION_NUM_TYPES];

	memset(entry, 0, sizeof(memorystatus_jetsam_snapshot_entry_t));

	entry->pid = p->p_pid;
	strlcpy(&entry->name[0], p->p_name, sizeof(entry->name));
	entry->priority = p->p_memstat_effectivepriority;

	memorystatus_get_task_page_counts(p->task, &pages, &max_pages_lifetime, &purgeable_pages);
	entry->pages              = (uint64_t)pages;
	entry->max_pages_lifetime = (uint64_t)max_pages_lifetime;
	entry->purgeable_pages    = (uint64_t)purgeable_pages;

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

	memorystatus_get_task_memory_region_count(p->task, &region_count);
	entry->jse_memory_region_count = region_count;

	entry->state     = memorystatus_build_state(p);
	entry->user_data = p->p_memstat_userdata;
	memcpy(&entry->uuid[0], &p->p_uuid[0], sizeof(p->p_uuid));
	entry->fds       = p->p_fd->fd_nfiles;

	absolutetime_to_microtime(get_task_cpu_time(p->task), &tv_sec, &tv_usec);
	entry->cpu_time.tv_sec = (int64_t)tv_sec;
	entry->cpu_time.tv_usec = (int64_t)tv_usec;

	assert(p->p_stats != NULL);
	entry->jse_starttime =  p->p_stats->ps_start;	/* abstime process started */
	entry->jse_killtime = 0;			/* abstime jetsam chose to kill process */
	entry->killed       = 0;			/* the jetsam kill cause */
	entry->jse_gencount = gencount;			/* indicates a pass through jetsam thread, when process was targeted to be killed */

	entry->jse_idle_delta = p->p_memstat_idle_delta; /* Most recent timespan spent in idle-band */

#if CONFIG_FREEZE
	entry->jse_thaw_count = p->p_memstat_thaw_count;
#else /* CONFIG_FREEZE */
	entry->jse_thaw_count = 0;
#endif /* CONFIG_FREEZE */

	proc_coalitionids(p, cids);
	entry->jse_coalition_jetsam_id = cids[COALITION_TYPE_JETSAM];

	return TRUE;	
}