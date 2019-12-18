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
struct log_c {int /*<<< orphan*/  luid; int /*<<< orphan*/  uuid; scalar_t__ in_sync_hint; } ;
struct dm_dirty_log {struct log_c* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_ULOG_RESUME ; 
 int dm_consult_userspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int userspace_resume(struct dm_dirty_log *log)
{
	int r;
	struct log_c *lc = log->context;

	lc->in_sync_hint = 0;
	r = dm_consult_userspace(lc->uuid, lc->luid, DM_ULOG_RESUME,
				 NULL, 0,
				 NULL, NULL);

	return r;
}