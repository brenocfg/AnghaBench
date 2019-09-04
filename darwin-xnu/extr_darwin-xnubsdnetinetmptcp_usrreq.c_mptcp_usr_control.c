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
struct socket {int dummy; } ;
struct so_cinforeq64 {int /*<<< orphan*/  scir_aux_len; int /*<<< orphan*/  scir_aux_data; int /*<<< orphan*/  scir_aux_type; int /*<<< orphan*/  scir_dst_len; int /*<<< orphan*/  scir_dst; int /*<<< orphan*/  scir_src_len; int /*<<< orphan*/  scir_src; int /*<<< orphan*/  scir_error; int /*<<< orphan*/  scir_ifindex; int /*<<< orphan*/  scir_flags; int /*<<< orphan*/  scir_cid; int /*<<< orphan*/  scr_cidp; int /*<<< orphan*/  scr_cnt; int /*<<< orphan*/  scr_aid; int /*<<< orphan*/  sar_aidp; int /*<<< orphan*/  sar_cnt; } ;
struct so_cinforeq32 {int /*<<< orphan*/  scir_aux_len; int /*<<< orphan*/  scir_aux_data; int /*<<< orphan*/  scir_aux_type; int /*<<< orphan*/  scir_dst_len; int /*<<< orphan*/  scir_dst; int /*<<< orphan*/  scir_src_len; int /*<<< orphan*/  scir_src; int /*<<< orphan*/  scir_error; int /*<<< orphan*/  scir_ifindex; int /*<<< orphan*/  scir_flags; int /*<<< orphan*/  scir_cid; int /*<<< orphan*/  scr_cidp; int /*<<< orphan*/  scr_cnt; int /*<<< orphan*/  scr_aid; int /*<<< orphan*/  sar_aidp; int /*<<< orphan*/  sar_cnt; } ;
struct so_cidreq64 {int /*<<< orphan*/  scir_aux_len; int /*<<< orphan*/  scir_aux_data; int /*<<< orphan*/  scir_aux_type; int /*<<< orphan*/  scir_dst_len; int /*<<< orphan*/  scir_dst; int /*<<< orphan*/  scir_src_len; int /*<<< orphan*/  scir_src; int /*<<< orphan*/  scir_error; int /*<<< orphan*/  scir_ifindex; int /*<<< orphan*/  scir_flags; int /*<<< orphan*/  scir_cid; int /*<<< orphan*/  scr_cidp; int /*<<< orphan*/  scr_cnt; int /*<<< orphan*/  scr_aid; int /*<<< orphan*/  sar_aidp; int /*<<< orphan*/  sar_cnt; } ;
struct so_cidreq32 {int /*<<< orphan*/  scir_aux_len; int /*<<< orphan*/  scir_aux_data; int /*<<< orphan*/  scir_aux_type; int /*<<< orphan*/  scir_dst_len; int /*<<< orphan*/  scir_dst; int /*<<< orphan*/  scir_src_len; int /*<<< orphan*/  scir_src; int /*<<< orphan*/  scir_error; int /*<<< orphan*/  scir_ifindex; int /*<<< orphan*/  scir_flags; int /*<<< orphan*/  scir_cid; int /*<<< orphan*/  scr_cidp; int /*<<< orphan*/  scr_cnt; int /*<<< orphan*/  scr_aid; int /*<<< orphan*/  sar_aidp; int /*<<< orphan*/  sar_cnt; } ;
struct so_aidreq64 {int /*<<< orphan*/  scir_aux_len; int /*<<< orphan*/  scir_aux_data; int /*<<< orphan*/  scir_aux_type; int /*<<< orphan*/  scir_dst_len; int /*<<< orphan*/  scir_dst; int /*<<< orphan*/  scir_src_len; int /*<<< orphan*/  scir_src; int /*<<< orphan*/  scir_error; int /*<<< orphan*/  scir_ifindex; int /*<<< orphan*/  scir_flags; int /*<<< orphan*/  scir_cid; int /*<<< orphan*/  scr_cidp; int /*<<< orphan*/  scr_cnt; int /*<<< orphan*/  scr_aid; int /*<<< orphan*/  sar_aidp; int /*<<< orphan*/  sar_cnt; } ;
struct so_aidreq32 {int /*<<< orphan*/  scir_aux_len; int /*<<< orphan*/  scir_aux_data; int /*<<< orphan*/  scir_aux_type; int /*<<< orphan*/  scir_dst_len; int /*<<< orphan*/  scir_dst; int /*<<< orphan*/  scir_src_len; int /*<<< orphan*/  scir_src; int /*<<< orphan*/  scir_error; int /*<<< orphan*/  scir_ifindex; int /*<<< orphan*/  scir_flags; int /*<<< orphan*/  scir_cid; int /*<<< orphan*/  scr_cidp; int /*<<< orphan*/  scr_cnt; int /*<<< orphan*/  scr_aid; int /*<<< orphan*/  sar_aidp; int /*<<< orphan*/  sar_cnt; } ;
struct proc {int dummy; } ;
struct mptses {int dummy; } ;
struct mppcb {scalar_t__ mpp_state; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  cifr ;
typedef  int /*<<< orphan*/  cidr ;
typedef  struct so_cinforeq64* caddr_t ;
typedef  int /*<<< orphan*/  aidr ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ MPPCB_STATE_DEAD ; 
#define  SIOCGASSOCIDS32 133 
#define  SIOCGASSOCIDS64 132 
#define  SIOCGCONNIDS32 131 
#define  SIOCGCONNIDS64 130 
#define  SIOCGCONNINFO32 129 
#define  SIOCGCONNINFO64 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct so_cinforeq64*,struct so_cinforeq64*,int) ; 
 struct mppcb* mpsotomppcb (struct socket*) ; 
 int mptcp_getassocids (struct mptses*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mptcp_getconnids (struct mptses*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mptcp_getconninfo (struct mptses*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpte_lock_assert_held (struct mptses*) ; 
 struct mptses* mptompte (struct mppcb*) ; 

__attribute__((used)) static int
mptcp_usr_control(struct socket *mp_so, u_long cmd, caddr_t data,
    struct ifnet *ifp, struct proc *p)
{
#pragma unused(ifp, p)
	struct mppcb *mpp = mpsotomppcb(mp_so);
	struct mptses *mpte;
	int error = 0;

	if (mpp == NULL || mpp->mpp_state == MPPCB_STATE_DEAD) {
		error = EINVAL;
		goto out;
	}
	mpte = mptompte(mpp);
	VERIFY(mpte != NULL);

	mpte_lock_assert_held(mpte);	/* same as MP socket lock */

	switch (cmd) {
	case SIOCGASSOCIDS32: {		/* struct so_aidreq32 */
		struct so_aidreq32 aidr;
		bcopy(data, &aidr, sizeof (aidr));
		error = mptcp_getassocids(mpte, &aidr.sar_cnt,
		    aidr.sar_aidp);
		if (error == 0)
			bcopy(&aidr, data, sizeof (aidr));
		break;
	}

	case SIOCGASSOCIDS64: {		/* struct so_aidreq64 */
		struct so_aidreq64 aidr;
		bcopy(data, &aidr, sizeof (aidr));
		error = mptcp_getassocids(mpte, &aidr.sar_cnt,
		    aidr.sar_aidp);
		if (error == 0)
			bcopy(&aidr, data, sizeof (aidr));
		break;
	}

	case SIOCGCONNIDS32: {		/* struct so_cidreq32 */
		struct so_cidreq32 cidr;
		bcopy(data, &cidr, sizeof (cidr));
		error = mptcp_getconnids(mpte, cidr.scr_aid, &cidr.scr_cnt,
		    cidr.scr_cidp);
		if (error == 0)
			bcopy(&cidr, data, sizeof (cidr));
		break;
	}

	case SIOCGCONNIDS64: {		/* struct so_cidreq64 */
		struct so_cidreq64 cidr;
		bcopy(data, &cidr, sizeof (cidr));
		error = mptcp_getconnids(mpte, cidr.scr_aid, &cidr.scr_cnt,
		    cidr.scr_cidp);
		if (error == 0)
			bcopy(&cidr, data, sizeof (cidr));
		break;
	}

	case SIOCGCONNINFO32: {		/* struct so_cinforeq32 */
		struct so_cinforeq32 cifr;
		bcopy(data, &cifr, sizeof (cifr));
		error = mptcp_getconninfo(mpte, &cifr.scir_cid,
		    &cifr.scir_flags, &cifr.scir_ifindex, &cifr.scir_error,
		    cifr.scir_src, &cifr.scir_src_len, cifr.scir_dst,
		    &cifr.scir_dst_len, &cifr.scir_aux_type, cifr.scir_aux_data,
		    &cifr.scir_aux_len);
		if (error == 0)
			bcopy(&cifr, data, sizeof (cifr));
		break;
	}

	case SIOCGCONNINFO64: {		/* struct so_cinforeq64 */
		struct so_cinforeq64 cifr;
		bcopy(data, &cifr, sizeof (cifr));
		error = mptcp_getconninfo(mpte, &cifr.scir_cid,
		    &cifr.scir_flags, &cifr.scir_ifindex, &cifr.scir_error,
		    cifr.scir_src, &cifr.scir_src_len, cifr.scir_dst,
		    &cifr.scir_dst_len, &cifr.scir_aux_type, cifr.scir_aux_data,
		    &cifr.scir_aux_len);
		if (error == 0)
			bcopy(&cifr, data, sizeof (cifr));
		break;
	}

	default:
		error = EOPNOTSUPP;
		break;
	}
out:
	return (error);
}