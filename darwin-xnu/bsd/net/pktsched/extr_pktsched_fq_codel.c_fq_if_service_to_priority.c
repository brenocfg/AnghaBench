#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int mbuf_svc_class_t ;
struct TYPE_3__ {int fqs_flags; } ;
typedef  TYPE_1__ fq_if_t ;

/* Variables and functions */
 int FQS_DRIVER_MANAGED ; 
 int /*<<< orphan*/  FQ_IF_AV_INDEX ; 
 int /*<<< orphan*/  FQ_IF_BE_INDEX ; 
 int /*<<< orphan*/  FQ_IF_BK_INDEX ; 
 int /*<<< orphan*/  FQ_IF_BK_SYS_INDEX ; 
 int /*<<< orphan*/  FQ_IF_CTL_INDEX ; 
 int /*<<< orphan*/  FQ_IF_OAM_INDEX ; 
 int /*<<< orphan*/  FQ_IF_RD_INDEX ; 
 int /*<<< orphan*/  FQ_IF_RV_INDEX ; 
 int /*<<< orphan*/  FQ_IF_SIG_INDEX ; 
 int /*<<< orphan*/  FQ_IF_VI_INDEX ; 
 int /*<<< orphan*/  FQ_IF_VO_INDEX ; 
#define  MBUF_SC_AV 138 
#define  MBUF_SC_BE 137 
#define  MBUF_SC_BK 136 
#define  MBUF_SC_BK_SYS 135 
#define  MBUF_SC_CTL 134 
#define  MBUF_SC_OAM 133 
#define  MBUF_SC_RD 132 
#define  MBUF_SC_RV 131 
#define  MBUF_SC_SIG 130 
#define  MBUF_SC_VI 129 
#define  MBUF_SC_VO 128 

__attribute__((used)) static inline u_int32_t
fq_if_service_to_priority(fq_if_t *fqs, mbuf_svc_class_t svc)
{
	u_int32_t pri;

	if (fqs->fqs_flags & FQS_DRIVER_MANAGED) {
		switch (svc) {
		case MBUF_SC_BK_SYS:
		case MBUF_SC_BK:
			pri = FQ_IF_BK_INDEX;
			break;
		case MBUF_SC_BE:
		case MBUF_SC_RD:
		case MBUF_SC_OAM:
			pri = FQ_IF_BE_INDEX;
			break;
		case MBUF_SC_AV:
		case MBUF_SC_RV:
		case MBUF_SC_VI:
		case MBUF_SC_SIG:
			pri = FQ_IF_VI_INDEX;
			break;
		case MBUF_SC_VO:
		case MBUF_SC_CTL:
			pri = FQ_IF_VO_INDEX;
			break;
		default:
			pri = FQ_IF_BE_INDEX; /* Use best effort by default */
			break;
		}
		return (pri);
	}

	/* scheduler is not managed by the driver */
	switch (svc) {
	case MBUF_SC_BK_SYS:
		pri = FQ_IF_BK_SYS_INDEX;
		break;
	case MBUF_SC_BK:
		pri = FQ_IF_BK_INDEX;
		break;
	case MBUF_SC_BE:
		pri = FQ_IF_BE_INDEX;
		break;
	case MBUF_SC_RD:
		pri = FQ_IF_RD_INDEX;
		break;
	case MBUF_SC_OAM:
		pri = FQ_IF_OAM_INDEX;
		break;
	case MBUF_SC_AV:
		pri = FQ_IF_AV_INDEX;
		break;
	case MBUF_SC_RV:
		pri = FQ_IF_RV_INDEX;
		break;
	case MBUF_SC_VI:
		pri = FQ_IF_VI_INDEX;
		break;
	case MBUF_SC_SIG:
		pri = FQ_IF_SIG_INDEX;
		break;
	case MBUF_SC_VO:
		pri = FQ_IF_VO_INDEX;
		break;
	case MBUF_SC_CTL:
		pri = FQ_IF_CTL_INDEX;
		break;
	default:
		pri = FQ_IF_BE_INDEX; /* Use best effort by default */
		break;
	}
	return (pri);
}