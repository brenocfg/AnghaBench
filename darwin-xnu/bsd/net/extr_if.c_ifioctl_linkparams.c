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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int64_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct tb_profile {int /*<<< orphan*/  percent; int /*<<< orphan*/  rate; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct proc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tbr_percent; int /*<<< orphan*/  tbr_rate_raw; } ;
struct ifclassq {TYPE_1__ ifcq_tbr; int /*<<< orphan*/  ifcq_type; } ;
struct ifnet {int /*<<< orphan*/  if_input_lt; int /*<<< orphan*/  if_output_lt; int /*<<< orphan*/  if_input_bw; int /*<<< orphan*/  if_output_bw; int /*<<< orphan*/  if_output_sched_model; struct ifclassq if_snd; } ;
struct if_linkparamsreq {int /*<<< orphan*/  iflpr_input_lt; int /*<<< orphan*/  iflpr_output_lt; int /*<<< orphan*/  iflpr_input_bw; int /*<<< orphan*/  iflpr_output_bw; int /*<<< orphan*/  iflpr_flags; int /*<<< orphan*/  iflpr_output_tbr_percent; int /*<<< orphan*/  iflpr_output_tbr_rate; int /*<<< orphan*/  iflpr_output_sched; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IFCQ_IS_ENABLED (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_IS_READY (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_LOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_TBR_IS_ENABLED (struct ifclassq*) ; 
 int /*<<< orphan*/  IFCQ_UNLOCK (struct ifclassq*) ; 
 int /*<<< orphan*/  IFLPRF_DRVMANAGED ; 
 int /*<<< orphan*/  IFNET_SCHED_MODEL_DRIVER_MANAGED ; 
 int /*<<< orphan*/  PKTSCHEDT_NONE ; 
#define  SIOCGIFLINKPARAMS 129 
#define  SIOCSIFLINKPARAMS 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ifclassq_tbr_set (struct ifclassq*,struct tb_profile*,int /*<<< orphan*/ ) ; 
 int proc_suser (struct proc*) ; 

__attribute__((used)) static __attribute__((noinline)) int
ifioctl_linkparams(struct ifnet *ifp, u_long cmd, caddr_t data, struct proc *p)
{
	struct if_linkparamsreq *iflpr =
	    (struct if_linkparamsreq *)(void *)data;
	struct ifclassq *ifq;
	int error = 0;

	VERIFY(ifp != NULL);
	ifq = &ifp->if_snd;

	switch (cmd) {
	case SIOCSIFLINKPARAMS: {		/* struct if_linkparamsreq */
		struct tb_profile tb = { 0, 0, 0 };

		if ((error = proc_suser(p)) != 0)
			break;


		IFCQ_LOCK(ifq);
		if (!IFCQ_IS_READY(ifq)) {
			error = ENXIO;
			IFCQ_UNLOCK(ifq);
			break;
		}
		bcopy(&iflpr->iflpr_output_tbr_rate, &tb.rate,
		    sizeof (tb.rate));
		bcopy(&iflpr->iflpr_output_tbr_percent, &tb.percent,
		    sizeof (tb.percent));
		error = ifclassq_tbr_set(ifq, &tb, TRUE);
		IFCQ_UNLOCK(ifq);
		break;
	}

	case SIOCGIFLINKPARAMS: {		/* struct if_linkparamsreq */
		u_int32_t sched_type = PKTSCHEDT_NONE, flags = 0;
		u_int64_t tbr_bw = 0, tbr_pct = 0;

		IFCQ_LOCK(ifq);

		if (IFCQ_IS_ENABLED(ifq))
			sched_type = ifq->ifcq_type;

		bcopy(&sched_type, &iflpr->iflpr_output_sched,
		    sizeof (iflpr->iflpr_output_sched));

		if (IFCQ_TBR_IS_ENABLED(ifq)) {
			tbr_bw = ifq->ifcq_tbr.tbr_rate_raw;
			tbr_pct = ifq->ifcq_tbr.tbr_percent;
		}
		bcopy(&tbr_bw, &iflpr->iflpr_output_tbr_rate,
		    sizeof (iflpr->iflpr_output_tbr_rate));
		bcopy(&tbr_pct, &iflpr->iflpr_output_tbr_percent,
		    sizeof (iflpr->iflpr_output_tbr_percent));
		IFCQ_UNLOCK(ifq);

		if (ifp->if_output_sched_model ==
		    IFNET_SCHED_MODEL_DRIVER_MANAGED)
			flags |= IFLPRF_DRVMANAGED;
		bcopy(&flags, &iflpr->iflpr_flags, sizeof (iflpr->iflpr_flags));
		bcopy(&ifp->if_output_bw, &iflpr->iflpr_output_bw,
		    sizeof (iflpr->iflpr_output_bw));
		bcopy(&ifp->if_input_bw, &iflpr->iflpr_input_bw,
		    sizeof (iflpr->iflpr_input_bw));
		bcopy(&ifp->if_output_lt, &iflpr->iflpr_output_lt,
		    sizeof (iflpr->iflpr_output_lt));
		bcopy(&ifp->if_input_lt, &iflpr->iflpr_input_lt,
		    sizeof (iflpr->iflpr_input_lt));
		break;
	}

	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (error);
}