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
#define  SCVAL_AV 137 
#define  SCVAL_BE 136 
#define  SCVAL_BK 135 
#define  SCVAL_BK_SYS 134 
#define  SCVAL_CTL 133 
#define  SCVAL_OAM 132 
#define  SCVAL_RD 131 
#define  SCVAL_RV 130 
#define  SCVAL_VI 129 
#define  SCVAL_VO 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 

mbuf_svc_class_t
m_service_class_from_val(u_int32_t v)
{
	mbuf_svc_class_t sc = MBUF_SC_BE;

	switch (v) {
	case SCVAL_BK_SYS:
		return (MBUF_SC_BK_SYS);

	case SCVAL_BK:
		return (MBUF_SC_BK);

	case SCVAL_BE:
		return (MBUF_SC_BE);

	case SCVAL_RD:
		return (MBUF_SC_RD);

	case SCVAL_OAM:
		return (MBUF_SC_OAM);

	case SCVAL_AV:
		return (MBUF_SC_AV);

	case SCVAL_RV:
		return (MBUF_SC_RV);

	case SCVAL_VI:
		return (MBUF_SC_VI);

	case SCVAL_VO:
		return (MBUF_SC_VO);

	case SCVAL_CTL:
		return (MBUF_SC_CTL);

	default:
		break;
	}

	VERIFY(0);
	/* NOTREACHED */
	return (sc);
}