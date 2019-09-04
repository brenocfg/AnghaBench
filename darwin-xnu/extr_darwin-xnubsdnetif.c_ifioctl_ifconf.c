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
struct ifconf64 {int /*<<< orphan*/  ifc_len; int /*<<< orphan*/  ifc_req; } ;
struct ifconf32 {int /*<<< orphan*/  ifc_len; int /*<<< orphan*/  ifc_req; } ;
typedef  int /*<<< orphan*/  ifc ;
typedef  struct ifconf64* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 
#define  OSIOCGIFCONF32 131 
#define  OSIOCGIFCONF64 130 
#define  SIOCGIFCONF32 129 
#define  SIOCGIFCONF64 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct ifconf64*,struct ifconf64*,int) ; 
 int ifconf (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __attribute__((noinline)) int
ifioctl_ifconf(u_long cmd, caddr_t data)
{
	int error = 0;

	switch (cmd) {
	case OSIOCGIFCONF32:			/* struct ifconf32 */
	case SIOCGIFCONF32: {			/* struct ifconf32 */
		struct ifconf32 ifc;
		bcopy(data, &ifc, sizeof (ifc));
		error = ifconf(cmd, CAST_USER_ADDR_T(ifc.ifc_req),
		    &ifc.ifc_len);
		bcopy(&ifc, data, sizeof (ifc));
		break;
	}

	case SIOCGIFCONF64:			/* struct ifconf64 */
	case OSIOCGIFCONF64: {			/* struct ifconf64 */
		struct ifconf64 ifc;
		bcopy(data, &ifc, sizeof (ifc));
		error = ifconf(cmd, ifc.ifc_req, &ifc.ifc_len);
		bcopy(&ifc, data, sizeof (ifc));
		break;
	}

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}