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
struct kev_msg {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ifnet_increment_generation (struct ifnet*) ; 
 int kev_post_msg (struct kev_msg*) ; 
 int /*<<< orphan*/  necp_update_all_clients () ; 

int
dlil_post_complete_msg(struct ifnet *ifp, struct kev_msg *event)
{
	if (ifp != NULL) {
		ifnet_increment_generation(ifp);
	}

#if NECP
	necp_update_all_clients();
#endif /* NECP */

	return (kev_post_msg(event));
}