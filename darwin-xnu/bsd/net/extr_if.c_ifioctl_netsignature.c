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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct ifnet {int dummy; } ;
struct if_nsreq {int ifnsr_len; int /*<<< orphan*/  ifnsr_flags; int /*<<< orphan*/  ifnsr_data; int /*<<< orphan*/  ifnsr_family; } ;
typedef  int /*<<< orphan*/  flags ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
#define  SIOCGIFNETSIGNATURE 129 
#define  SIOCSIFNETSIGNATURE 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ifnet_get_netsignature (struct ifnet*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ifnet_set_netsignature (struct ifnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __attribute__((noinline)) int
ifioctl_netsignature(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct if_nsreq *ifnsr = (struct if_nsreq *)(void *)data;
	u_int16_t flags;
	int error = 0;

	VERIFY(ifp != NULL);

	switch (cmd) {
	case SIOCSIFNETSIGNATURE:		/* struct if_nsreq */
		if (ifnsr->ifnsr_len > sizeof (ifnsr->ifnsr_data)) {
			error = EINVAL;
			break;
		}
		bcopy(&ifnsr->ifnsr_flags, &flags, sizeof (flags));
		error = ifnet_set_netsignature(ifp, ifnsr->ifnsr_family,
		    ifnsr->ifnsr_len, flags, ifnsr->ifnsr_data);
		break;

	case SIOCGIFNETSIGNATURE:		/* struct if_nsreq */
		ifnsr->ifnsr_len = sizeof (ifnsr->ifnsr_data);
		error = ifnet_get_netsignature(ifp, ifnsr->ifnsr_family,
		    &ifnsr->ifnsr_len, &flags, ifnsr->ifnsr_data);
		if (error == 0)
			bcopy(&flags, &ifnsr->ifnsr_flags, sizeof (flags));
		else
			ifnsr->ifnsr_len = 0;
		break;

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}