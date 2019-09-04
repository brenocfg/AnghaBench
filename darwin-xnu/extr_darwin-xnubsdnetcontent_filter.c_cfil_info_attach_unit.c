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
typedef  scalar_t__ uint32_t ;
struct socket {int dummy; } ;
struct content_filter {scalar_t__ cf_necp_control_unit; int /*<<< orphan*/  cf_sock_count; int /*<<< orphan*/  cf_sock_entries; } ;
struct cfil_info {struct cfil_entry* cfi_entries; } ;
struct cfil_entry {int /*<<< orphan*/  cfe_flags; scalar_t__ cfe_necp_control_unit; struct content_filter* cfe_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFEF_CFIL_ATTACHED ; 
 int /*<<< orphan*/  CFIL_LOG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int MAX_CONTENT_FILTER ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cfil_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfe_link ; 
 int /*<<< orphan*/  cfil_lck_rw ; 
 int /*<<< orphan*/  cfil_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfil_rw_unlock_exclusive (int /*<<< orphan*/ *) ; 
 struct content_filter** content_filters ; 
 int /*<<< orphan*/  socket_lock_assert_owned (struct socket*) ; 
 int /*<<< orphan*/  verify_content_filter (struct content_filter*) ; 

int
cfil_info_attach_unit(struct socket *so, uint32_t filter_control_unit, struct cfil_info *cfil_info)
{
	int kcunit;
	int attached = 0;

	CFIL_LOG(LOG_INFO, "");

	socket_lock_assert_owned(so);

	cfil_rw_lock_exclusive(&cfil_lck_rw);

	for (kcunit = 1;
		content_filters != NULL && kcunit <= MAX_CONTENT_FILTER;
		kcunit++) {
		struct content_filter *cfc = content_filters[kcunit - 1];
		struct cfil_entry *entry;

		if (cfc == NULL)
			continue;
		if (cfc->cf_necp_control_unit != filter_control_unit)
			continue;

		entry = &cfil_info->cfi_entries[kcunit - 1];

		entry->cfe_filter = cfc;
		entry->cfe_necp_control_unit = filter_control_unit;
		TAILQ_INSERT_TAIL(&cfc->cf_sock_entries, entry, cfe_link);
		cfc->cf_sock_count++;
		verify_content_filter(cfc);
		attached = 1;
		entry->cfe_flags |= CFEF_CFIL_ATTACHED;
		break;
	}

	cfil_rw_unlock_exclusive(&cfil_lck_rw);

	return (attached);
}