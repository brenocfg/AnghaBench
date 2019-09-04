#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
struct TYPE_2__ {struct ifnet* ifp; } ;
struct ifnet {TYPE_1__ if_delegated; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ if_functional_type (struct ifnet*,int) ; 

__attribute__((used)) static bool
necp_ifnet_matches_type(struct ifnet *ifp, u_int8_t interface_type, bool check_delegates)
{
	struct ifnet *check_ifp = ifp;
	while (check_ifp) {
		if (if_functional_type(check_ifp, TRUE) == interface_type) {
			return (TRUE);
		}
		if (!check_delegates) {
			break;
		}
		check_ifp = check_ifp->if_delegated.ifp;

	}
	return (FALSE);
}