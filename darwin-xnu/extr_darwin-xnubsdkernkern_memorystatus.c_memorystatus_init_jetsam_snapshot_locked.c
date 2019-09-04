#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint32_t ;
typedef  TYPE_1__* proc_t ;
struct TYPE_11__ {unsigned int entry_count; scalar_t__ js_gencount; scalar_t__ notification_time; int /*<<< orphan*/  snapshot_time; int /*<<< orphan*/ * entries; } ;
typedef  TYPE_2__ memorystatus_jetsam_snapshot_t ;
typedef  int /*<<< orphan*/  memorystatus_jetsam_snapshot_entry_t ;
struct TYPE_10__ {int /*<<< orphan*/ * p_uuid; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  MEMORYSTATUS_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 TYPE_1__* memorystatus_get_first_proc_locked (unsigned int*,int /*<<< orphan*/ ) ; 
 TYPE_1__* memorystatus_get_next_proc_locked (unsigned int*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ memorystatus_init_jetsam_snapshot_entry_locked (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memorystatus_init_snapshot_vmstats (TYPE_2__*) ; 
 TYPE_2__* memorystatus_jetsam_snapshot ; 
 unsigned int memorystatus_jetsam_snapshot_count ; 
 unsigned int memorystatus_jetsam_snapshot_max ; 
 int /*<<< orphan*/  proc_list_mlock ; 

__attribute__((used)) static void
memorystatus_init_jetsam_snapshot_locked(memorystatus_jetsam_snapshot_t *od_snapshot, uint32_t ods_list_count )
{
	proc_t p, next_p;
	unsigned int b = 0, i = 0;

	memorystatus_jetsam_snapshot_t *snapshot = NULL;
	memorystatus_jetsam_snapshot_entry_t *snapshot_list = NULL;
	unsigned int snapshot_max = 0;

	LCK_MTX_ASSERT(proc_list_mlock, LCK_MTX_ASSERT_OWNED);

	if (od_snapshot) {
		/*
		 * This is an on_demand snapshot
		 */
		snapshot      = od_snapshot;
		snapshot_list = od_snapshot->entries;
		snapshot_max  = ods_list_count;
	} else {
		/*
		 * This is a jetsam event snapshot
		 */
		snapshot      = memorystatus_jetsam_snapshot;
		snapshot_list = memorystatus_jetsam_snapshot->entries;
		snapshot_max  = memorystatus_jetsam_snapshot_max;
	}

	/*
	 * Init the snapshot header information
	 */
	memorystatus_init_snapshot_vmstats(snapshot);
	snapshot->snapshot_time = mach_absolute_time();
	snapshot->notification_time = 0;
	snapshot->js_gencount = 0;

	next_p = memorystatus_get_first_proc_locked(&b, TRUE);
	while (next_p) {
		p = next_p;
		next_p = memorystatus_get_next_proc_locked(&b, p, TRUE);
	        
		if (FALSE == memorystatus_init_jetsam_snapshot_entry_locked(p, &snapshot_list[i], snapshot->js_gencount)) {
			continue;
		}
		
		MEMORYSTATUS_DEBUG(0, "jetsam snapshot pid %d, uuid = %02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
			p->p_pid, 
			p->p_uuid[0], p->p_uuid[1], p->p_uuid[2], p->p_uuid[3], p->p_uuid[4], p->p_uuid[5], p->p_uuid[6], p->p_uuid[7],
			p->p_uuid[8], p->p_uuid[9], p->p_uuid[10], p->p_uuid[11], p->p_uuid[12], p->p_uuid[13], p->p_uuid[14], p->p_uuid[15]);

		if (++i == snapshot_max) {
			break;
		} 	
	}

	snapshot->entry_count = i;

	if (!od_snapshot) {
		/* update the system buffer count */
		memorystatus_jetsam_snapshot_count = i;
	}
}