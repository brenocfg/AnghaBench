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
typedef  int /*<<< orphan*/  uint64_t ;
struct log_c {int /*<<< orphan*/  uuid; } ;
struct dm_dirty_log {struct log_c* context; } ;
typedef  int /*<<< orphan*/  region_t ;
typedef  int /*<<< orphan*/  region64 ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  in_sync ;

/* Variables and functions */
 int /*<<< orphan*/  DM_ULOG_IN_SYNC ; 
 int EWOULDBLOCK ; 
 int userspace_do_request (struct log_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,size_t*) ; 

__attribute__((used)) static int userspace_in_sync(struct dm_dirty_log *log, region_t region,
			     int can_block)
{
	int r;
	uint64_t region64 = region;
	int64_t in_sync;
	size_t rdata_size;
	struct log_c *lc = log->context;

	/*
	 * We can never respond directly - even if in_sync_hint is
	 * set.  This is because another machine could see a device
	 * failure and mark the region out-of-sync.  If we don't go
	 * to userspace to ask, we might think the region is in-sync
	 * and allow a read to pick up data that is stale.  (This is
	 * very unlikely if a device actually fails; but it is very
	 * likely if a connection to one device from one machine fails.)
	 *
	 * There still might be a problem if the mirror caches the region
	 * state as in-sync... but then this call would not be made.  So,
	 * that is a mirror problem.
	 */
	if (!can_block)
		return -EWOULDBLOCK;

	rdata_size = sizeof(in_sync);
	r = userspace_do_request(lc, lc->uuid, DM_ULOG_IN_SYNC,
				 (char *)&region64, sizeof(region64),
				 (char *)&in_sync, &rdata_size);
	return (r) ? 0 : (int)in_sync;
}