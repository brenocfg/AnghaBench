#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ count; } ;

/* Variables and functions */
 int COALITION_SORT_DEFAULT ; 
 int EINVAL ; 
#define  JETSAM_PRIORITY_FOREGROUND 128 
 int JETSAM_SORT_DEFAULT ; 
 unsigned int MEMSTAT_BUCKET_COUNT ; 
 int /*<<< orphan*/  memorystatus_sort_by_largest_coalition_locked (unsigned int,int) ; 
 int /*<<< orphan*/  memorystatus_sort_by_largest_process_locked (unsigned int) ; 
 TYPE_1__* memstat_bucket ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

__attribute__((used)) static int memorystatus_sort_bucket(unsigned int bucket_index, int sort_order)
{
	int coal_sort_order;

	/*
	 * Verify the jetsam priority
	 */
        if (bucket_index >= MEMSTAT_BUCKET_COUNT) {
		return(EINVAL);
        }

#if DEVELOPMENT || DEBUG
        if (sort_order == JETSAM_SORT_DEFAULT) {
		coal_sort_order = COALITION_SORT_DEFAULT;
	} else {
		coal_sort_order = sort_order;		/* only used for testing scenarios */
	}
#else
	/* Verify default */
        if (sort_order == JETSAM_SORT_DEFAULT) {
		coal_sort_order = COALITION_SORT_DEFAULT;
	} else {
		return(EINVAL);
	}
#endif

	proc_list_lock();
	
	if (memstat_bucket[bucket_index].count == 0) {
		proc_list_unlock();
		return (0);
	}

	switch (bucket_index) {
	case JETSAM_PRIORITY_FOREGROUND:
		if (memorystatus_sort_by_largest_coalition_locked(bucket_index, coal_sort_order) == 0) {
			/*
			 * Fall back to per process sorting when zero coalitions are found.
			 */
			memorystatus_sort_by_largest_process_locked(bucket_index);
		}
		break;
	default:
		memorystatus_sort_by_largest_process_locked(bucket_index);
		break;
	}
	proc_list_unlock();
	
        return(0);
}