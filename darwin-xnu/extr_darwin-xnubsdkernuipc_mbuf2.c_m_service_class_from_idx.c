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
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_SC_AV ; 
 int /*<<< orphan*/  MBUF_SC_BE ; 
 int /*<<< orphan*/  MBUF_SC_BK ; 
 int /*<<< orphan*/  MBUF_SC_BK_SYS ; 
 int /*<<< orphan*/  MBUF_SC_CTL ; 
 int /*<<< orphan*/  MBUF_SC_OAM ; 
 int /*<<< orphan*/  MBUF_SC_RD ; 
 int /*<<< orphan*/  MBUF_SC_RV ; 
 int /*<<< orphan*/  MBUF_SC_VI ; 
 int /*<<< orphan*/  MBUF_SC_VO ; 
#define  SCIDX_AV 137 
#define  SCIDX_BE 136 
#define  SCIDX_BK 135 
#define  SCIDX_BK_SYS 134 
#define  SCIDX_CTL 133 
#define  SCIDX_OAM 132 
#define  SCIDX_RD 131 
#define  SCIDX_RV 130 
#define  SCIDX_VI 129 
#define  SCIDX_VO 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 

mbuf_svc_class_t
m_service_class_from_idx(u_int32_t i)
{
	mbuf_svc_class_t sc = MBUF_SC_BE;

	switch (i) {
	case SCIDX_BK_SYS:
		return (MBUF_SC_BK_SYS);

	case SCIDX_BK:
		return (MBUF_SC_BK);

	case SCIDX_BE:
		return (MBUF_SC_BE);

	case SCIDX_RD:
		return (MBUF_SC_RD);

	case SCIDX_OAM:
		return (MBUF_SC_OAM);

	case SCIDX_AV:
		return (MBUF_SC_AV);

	case SCIDX_RV:
		return (MBUF_SC_RV);

	case SCIDX_VI:
		return (MBUF_SC_VI);

	case SCIDX_VO:
		return (MBUF_SC_VO);

	case SCIDX_CTL:
		return (MBUF_SC_CTL);

	default:
		break;
	}

	VERIFY(0);
	/* NOTREACHED */
	return (sc);
}