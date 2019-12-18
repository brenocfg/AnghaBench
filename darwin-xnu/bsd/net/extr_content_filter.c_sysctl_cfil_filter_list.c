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
typedef  size_t u_int32_t ;
struct sysctl_req {scalar_t__ newptr; scalar_t__ oldptr; size_t oldidx; } ;
struct sysctl_oid {int dummy; } ;
struct content_filter {int /*<<< orphan*/  cf_necp_control_unit; int /*<<< orphan*/  cf_sock_count; int /*<<< orphan*/  cf_flags; int /*<<< orphan*/  cf_kcunit; } ;
struct cfil_filter_stat {int cfs_len; int /*<<< orphan*/  cfs_necp_control_unit; int /*<<< orphan*/  cfs_sock_count; int /*<<< orphan*/  cfs_flags; int /*<<< orphan*/  cfs_filter_id; } ;

/* Variables and functions */
 int EPERM ; 
 size_t MAX_CONTENT_FILTER ; 
 int SYSCTL_OUT (struct sysctl_req*,struct cfil_filter_stat*,int) ; 
 scalar_t__ USER_ADDR_NULL ; 
 int /*<<< orphan*/  bzero (struct cfil_filter_stat*,int) ; 
 int /*<<< orphan*/  cfil_filter_show (size_t) ; 
 int /*<<< orphan*/  cfil_lck_rw ; 
 int /*<<< orphan*/  cfil_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_unlock_shared (int /*<<< orphan*/ *) ; 
 struct content_filter** content_filters ; 

int
sysctl_cfil_filter_list(struct sysctl_oid *oidp, void *arg1, int arg2,
	struct sysctl_req *req)
{
#pragma unused(oidp, arg1, arg2)
	int error = 0;
	size_t len = 0;
	u_int32_t i;

	/* Read only  */
	if (req->newptr != USER_ADDR_NULL)
		return (EPERM);

	cfil_rw_lock_shared(&cfil_lck_rw);

	for (i = 0; content_filters != NULL && i < MAX_CONTENT_FILTER; i++) {
		struct cfil_filter_stat filter_stat;
		struct content_filter *cfc = content_filters[i];

		if (cfc == NULL)
			continue;

		/* If just asking for the size */
		if (req->oldptr == USER_ADDR_NULL) {
			len += sizeof(struct cfil_filter_stat);
			continue;
		}

		bzero(&filter_stat, sizeof(struct cfil_filter_stat));
		filter_stat.cfs_len = sizeof(struct cfil_filter_stat);
		filter_stat.cfs_filter_id = cfc->cf_kcunit;
		filter_stat.cfs_flags = cfc->cf_flags;
		filter_stat.cfs_sock_count = cfc->cf_sock_count;
		filter_stat.cfs_necp_control_unit = cfc->cf_necp_control_unit;

		error = SYSCTL_OUT(req, &filter_stat,
			sizeof (struct cfil_filter_stat));
		if (error != 0)
			break;
	}
	/* If just asking for the size */
	if (req->oldptr == USER_ADDR_NULL)
		req->oldidx = len;

	cfil_rw_unlock_shared(&cfil_lck_rw);

#if SHOW_DEBUG
	if (req->oldptr != USER_ADDR_NULL) {
		for (i = 1; content_filters != NULL && i <= MAX_CONTENT_FILTER; i++) {
			cfil_filter_show(i);
		}
	}
#endif

	return (error);
}