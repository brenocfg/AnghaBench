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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;
struct if_qstatsreq {int /*<<< orphan*/  ifqr_len; int /*<<< orphan*/  ifqr_buf; int /*<<< orphan*/  ifqr_slot; } ;
typedef  int /*<<< orphan*/  ifqr_slot ;
typedef  int /*<<< orphan*/  ifqr_len ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  SIOCGIFQUEUESTATS 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ifclassq_getqstats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __attribute__((noinline)) int
ifioctl_qstats(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct if_qstatsreq *ifqr = (struct if_qstatsreq *)(void *)data;
	u_int32_t ifqr_len, ifqr_slot;
	int error = 0;

	VERIFY(ifp != NULL);

	switch (cmd) {
	case SIOCGIFQUEUESTATS: {		/* struct if_qstatsreq */
		bcopy(&ifqr->ifqr_slot, &ifqr_slot, sizeof (ifqr_slot));
		bcopy(&ifqr->ifqr_len, &ifqr_len, sizeof (ifqr_len));
		error = ifclassq_getqstats(&ifp->if_snd, ifqr_slot,
		    ifqr->ifqr_buf, &ifqr_len);
		if (error != 0)
			ifqr_len = 0;
		bcopy(&ifqr_len, &ifqr->ifqr_len, sizeof (ifqr_len));
		break;
	}

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}