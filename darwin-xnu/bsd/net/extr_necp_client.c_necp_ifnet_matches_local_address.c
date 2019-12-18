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
typedef  int /*<<< orphan*/  u_int ;
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_index; } ;
struct ifaddr {int dummy; } ;
struct TYPE_4__ {scalar_t__ sin_port; } ;
struct TYPE_3__ {scalar_t__ sin6_scope_id; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int FALSE ; 
 int /*<<< orphan*/  IFSCOPE_NONE ; 
 TYPE_2__* SIN (struct sockaddr_storage*) ; 
 TYPE_1__* SIN6 (struct sockaddr_storage*) ; 
 struct ifaddr* ifa_ifwithaddr_scoped_locked (struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifaddr_release (struct ifaddr*) ; 
 int /*<<< orphan*/  sa_copy (struct sockaddr*,struct sockaddr_storage*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
necp_ifnet_matches_local_address(struct ifnet *ifp, struct sockaddr *sa)
{
	struct ifaddr *ifa = NULL;
	bool matched_local_address = FALSE;

	// Transform sa into the ifaddr form
	// IPv6 Scope IDs are always embedded in the ifaddr list
	struct sockaddr_storage address;
	u_int ifscope = IFSCOPE_NONE;
	(void)sa_copy(sa, &address, &ifscope);
	SIN(&address)->sin_port = 0;
	if (address.ss_family == AF_INET6) {
		SIN6(&address)->sin6_scope_id = 0;
	}

	ifa = ifa_ifwithaddr_scoped_locked((struct sockaddr *)&address, ifp->if_index);
	matched_local_address = (ifa != NULL);

	if (ifa) {
		ifaddr_release(ifa);
	}

	return (matched_local_address);
}