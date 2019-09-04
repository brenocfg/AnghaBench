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
struct TYPE_2__ {struct ifnet* ifp; } ;
struct ifnet {TYPE_1__ if_delegated; int /*<<< orphan*/  if_xname; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  IFXNAMSIZ ; 
 int TRUE ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
necp_ifnet_matches_name(struct ifnet *ifp, const char *interface_name, bool check_delegates)
{
	struct ifnet *check_ifp = ifp;
	while (check_ifp) {
		if (strncmp(check_ifp->if_xname, interface_name, IFXNAMSIZ) == 0) {
			return (TRUE);
		}
		if (!check_delegates) {
			break;
		}
		check_ifp = check_ifp->if_delegated.ifp;
	}
	return (FALSE);
}