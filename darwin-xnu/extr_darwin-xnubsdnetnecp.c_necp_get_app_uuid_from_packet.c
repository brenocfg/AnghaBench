#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
struct necp_uuid_id_mapping {int /*<<< orphan*/  uuid; } ;
struct TYPE_4__ {scalar_t__ necp_app_id; } ;
struct TYPE_3__ {TYPE_2__ necp_mtag; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int EINVAL ; 
 int FALSE ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 struct necp_uuid_id_mapping* necp_uuid_lookup_uuid_with_app_id_locked (scalar_t__) ; 
 int /*<<< orphan*/  uuid_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
necp_get_app_uuid_from_packet(struct mbuf *packet,
							  uuid_t app_uuid)
{
	if (packet == NULL || !(packet->m_flags & M_PKTHDR)) {
		return (EINVAL);
	}

	bool found_mapping = FALSE;
	if (packet->m_pkthdr.necp_mtag.necp_app_id != 0) {
		lck_rw_lock_shared(&necp_kernel_policy_lock);
		struct necp_uuid_id_mapping *entry = necp_uuid_lookup_uuid_with_app_id_locked(packet->m_pkthdr.necp_mtag.necp_app_id);
		if (entry != NULL) {
			uuid_copy(app_uuid, entry->uuid);
			found_mapping = true;
		}
		lck_rw_done(&necp_kernel_policy_lock);
	}
	if (!found_mapping) {
		uuid_clear(app_uuid);
	}
	return (0);
}