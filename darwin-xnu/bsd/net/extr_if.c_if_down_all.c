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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNET_FAMILY_ANY ; 
 int /*<<< orphan*/  dlil_proto_unplumb_all (struct ifnet*) ; 
 int /*<<< orphan*/  if_down (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_list_free (struct ifnet**) ; 
 scalar_t__ ifnet_list_get_all (int /*<<< orphan*/ ,struct ifnet***,size_t*) ; 

int
if_down_all(void)
{
	struct ifnet **ifp;
	u_int32_t	count;
	u_int32_t	i;

	if (ifnet_list_get_all(IFNET_FAMILY_ANY, &ifp, &count) == 0) {
		for (i = 0; i < count; i++) {
			if_down(ifp[i]);
			dlil_proto_unplumb_all(ifp[i]);
		}
		ifnet_list_free(ifp);
	}

	return (0);
}