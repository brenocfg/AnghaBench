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
struct log_c {struct log_c* usr_argv_str; scalar_t__ log_dev; int /*<<< orphan*/  ti; int /*<<< orphan*/  luid; int /*<<< orphan*/  uuid; } ;
struct dm_dirty_log {struct log_c* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_ULOG_DTR ; 
 int /*<<< orphan*/  dm_consult_userspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_put_device (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct log_c*) ; 

__attribute__((used)) static void userspace_dtr(struct dm_dirty_log *log)
{
	struct log_c *lc = log->context;

	(void) dm_consult_userspace(lc->uuid, lc->luid, DM_ULOG_DTR,
				 NULL, 0,
				 NULL, NULL);

	if (lc->log_dev)
		dm_put_device(lc->ti, lc->log_dev);

	kfree(lc->usr_argv_str);
	kfree(lc);

	return;
}