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
struct log_c {scalar_t__ in_sync_hint; scalar_t__ region_count; int /*<<< orphan*/  uuid; } ;
struct dm_dirty_log {struct log_c* context; } ;
typedef  int region_t ;
typedef  int /*<<< orphan*/  pkg ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM_ULOG_GET_RESYNC_WORK ; 
 int userspace_do_request (struct log_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t*) ; 

__attribute__((used)) static int userspace_get_resync_work(struct dm_dirty_log *log, region_t *region)
{
	int r;
	size_t rdata_size;
	struct log_c *lc = log->context;
	struct {
		int64_t i; /* 64-bit for mix arch compatibility */
		region_t r;
	} pkg;

	if (lc->in_sync_hint >= lc->region_count)
		return 0;

	rdata_size = sizeof(pkg);
	r = userspace_do_request(lc, lc->uuid, DM_ULOG_GET_RESYNC_WORK,
				 NULL, 0,
				 (char *)&pkg, &rdata_size);

	*region = pkg.r;
	return (r) ? r : (int)pkg.i;
}