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
struct ifnet {int if_updatemcasts; } ;
typedef  scalar_t__ errno_t ;

/* Variables and functions */
 scalar_t__ EAFNOSUPPORT ; 
 int /*<<< orphan*/  SIOCADDMULTI ; 
 char* if_name (struct ifnet*) ; 
 scalar_t__ ifnet_ioctl (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,int,scalar_t__) ; 

errno_t
if_mcasts_update(struct ifnet *ifp)
{
	errno_t err;

	err = ifnet_ioctl(ifp, 0, SIOCADDMULTI, NULL);
	if (err == EAFNOSUPPORT)
		err = 0;
	printf("%s: %s %d suspended link-layer multicast membership(s) "
	    "(err=%d)\n", if_name(ifp),
	    (err == 0 ? "successfully restored" : "failed to restore"),
	    ifp->if_updatemcasts, err);

	/* just return success */
	return (0);
}