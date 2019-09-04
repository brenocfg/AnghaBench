#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uthread_t ;
struct _throttle_io_info_t {int /*<<< orphan*/ * throttle_uthlist; int /*<<< orphan*/ * throttle_last_IO_timestamp; int /*<<< orphan*/ * throttle_start_IO_period_timestamp; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_6__ {int uu_on_throttlelist; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int THROTTLE_LEVEL_END ; 
 size_t THROTTLE_LEVEL_NONE ; 
 int THROTTLE_LEVEL_START ; 
 int THROTTLE_LEVEL_THROTTLED ; 
 scalar_t__ TRUE ; 
 int throttle_timer_start (struct _throttle_io_info_t*,scalar_t__,int) ; 
 int /*<<< orphan*/  uu_throttlelist ; 

__attribute__((used)) static int
throttle_add_to_list(struct _throttle_io_info_t *info, uthread_t ut, int mylevel, boolean_t insert_tail)
{
	boolean_t start_timer = FALSE;
	int level = THROTTLE_LEVEL_START;

	if (TAILQ_EMPTY(&info->throttle_uthlist[mylevel])) {
		info->throttle_start_IO_period_timestamp[mylevel] = info->throttle_last_IO_timestamp[mylevel];
		start_timer = TRUE;
	}

	if (insert_tail == TRUE)
		TAILQ_INSERT_TAIL(&info->throttle_uthlist[mylevel], ut, uu_throttlelist);
	else
		TAILQ_INSERT_HEAD(&info->throttle_uthlist[mylevel], ut, uu_throttlelist);

	ut->uu_on_throttlelist = mylevel;

	if (start_timer == TRUE) {
		/* we may need to start or rearm the timer */
		level = throttle_timer_start(info, FALSE, THROTTLE_LEVEL_START);

		if (level == THROTTLE_LEVEL_END) {
			if (ut->uu_on_throttlelist >= THROTTLE_LEVEL_THROTTLED) {
				TAILQ_REMOVE(&info->throttle_uthlist[ut->uu_on_throttlelist], ut, uu_throttlelist);

				ut->uu_on_throttlelist = THROTTLE_LEVEL_NONE;
			}
		}
	}
	return (level);
}