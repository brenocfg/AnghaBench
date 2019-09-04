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
struct ifnet {int dummy; } ;
struct if_protolistreq64 {int /*<<< orphan*/  ifpl_list; int /*<<< orphan*/  ifpl_count; int /*<<< orphan*/  ifpl_reserved; } ;
struct if_protolistreq32 {int /*<<< orphan*/  ifpl_list; int /*<<< orphan*/  ifpl_count; int /*<<< orphan*/  ifpl_reserved; } ;
typedef  int /*<<< orphan*/  ifpl ;
typedef  struct if_protolistreq64* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
#define  SIOCGIFPROTOLIST32 129 
#define  SIOCGIFPROTOLIST64 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct if_protolistreq64*,struct if_protolistreq64*,int) ; 
 int ifioctl_get_protolist (struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __attribute__((noinline)) int
ifioctl_protolist(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	int error = 0;

	switch (cmd) {
	case SIOCGIFPROTOLIST32: {		/* struct if_protolistreq32 */
		struct if_protolistreq32 	ifpl;

		bcopy(data, &ifpl, sizeof(ifpl));
		if (ifpl.ifpl_reserved != 0) {
			error = EINVAL;
			break;
		}
		error = ifioctl_get_protolist(ifp, &ifpl.ifpl_count,
		    CAST_USER_ADDR_T(ifpl.ifpl_list));
		bcopy(&ifpl, data, sizeof(ifpl));
		break;
	}
	case SIOCGIFPROTOLIST64: {		/* struct if_protolistreq64 */
		struct if_protolistreq64 	ifpl;

		bcopy(data, &ifpl, sizeof(ifpl));
		if (ifpl.ifpl_reserved != 0) {
			error = EINVAL;
			break;
		}
		error = ifioctl_get_protolist(ifp, &ifpl.ifpl_count,
		    ifpl.ifpl_list);
		bcopy(&ifpl, data, sizeof(ifpl));
		break;
	}
	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}