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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  scalar_t__ user_addr_t ;
typedef  size_t u_int32_t ;
struct ifnet {size_t if_agentcount; int /*<<< orphan*/ * if_agentids; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNET_LCK_ASSERT_SHARED ; 
 scalar_t__ USER_ADDR_NULL ; 
 int copyout (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  ifnet_lock_assert (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuid_is_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ifioctl_getnetagents(struct ifnet *ifp, u_int32_t *count, user_addr_t uuid_p)
{
	int error = 0;
	u_int32_t index = 0;
	u_int32_t valid_netagent_count = 0;
	*count = 0;

	ifnet_lock_assert(ifp, IFNET_LCK_ASSERT_SHARED);

	if (ifp->if_agentids != NULL) {
		for (index = 0; index < ifp->if_agentcount; index++) {
			uuid_t *netagent_uuid = &(ifp->if_agentids[index]);
			if (!uuid_is_null(*netagent_uuid)) {
				if (uuid_p != USER_ADDR_NULL) {
					error = copyout(netagent_uuid,
						uuid_p + sizeof(uuid_t) * valid_netagent_count,
						sizeof(uuid_t));
					if (error != 0) {
						return (error);
					}
				}
				valid_netagent_count++;
			}
		}
	}
	*count = valid_netagent_count;

	return (0);
}