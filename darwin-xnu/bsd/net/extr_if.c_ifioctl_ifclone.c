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
struct if_clonereq64 {int /*<<< orphan*/  ifcru_buffer; int /*<<< orphan*/  ifcr_total; int /*<<< orphan*/  ifcr_count; } ;
struct if_clonereq32 {int /*<<< orphan*/  ifcru_buffer; int /*<<< orphan*/  ifcr_total; int /*<<< orphan*/  ifcr_count; } ;
typedef  int /*<<< orphan*/  ifcr ;
typedef  struct if_clonereq64* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 
#define  SIOCIFGCLONERS32 129 
#define  SIOCIFGCLONERS64 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct if_clonereq64*,struct if_clonereq64*,int) ; 
 int if_clone_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __attribute__((noinline)) int
ifioctl_ifclone(u_long cmd, caddr_t data)
{
	int error = 0;

	switch (cmd) {
	case SIOCIFGCLONERS32: {		/* struct if_clonereq32 */
		struct if_clonereq32 ifcr;
		bcopy(data, &ifcr, sizeof (ifcr));
		error = if_clone_list(ifcr.ifcr_count, &ifcr.ifcr_total,
		    CAST_USER_ADDR_T(ifcr.ifcru_buffer));
		bcopy(&ifcr, data, sizeof (ifcr));
		break;
	}

	case SIOCIFGCLONERS64: {		/* struct if_clonereq64 */
		struct if_clonereq64 ifcr;
		bcopy(data, &ifcr, sizeof (ifcr));
		error = if_clone_list(ifcr.ifcr_count, &ifcr.ifcr_total,
		    ifcr.ifcru_buffer);
		bcopy(&ifcr, data, sizeof (ifcr));
		break;
	}

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}