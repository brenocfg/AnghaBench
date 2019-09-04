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
struct TYPE_3__ {int pktsched_ptype; int /*<<< orphan*/  pktsched_pkt; } ;
typedef  TYPE_1__ pktsched_pkt_t ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_SC_UNSPEC ; 
#define  QP_MBUF 128 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_get_service_class (int /*<<< orphan*/ ) ; 

mbuf_svc_class_t
pktsched_get_pkt_svc(pktsched_pkt_t *pkt)
{
	mbuf_svc_class_t svc = MBUF_SC_UNSPEC;

	switch (pkt->pktsched_ptype) {
	case QP_MBUF:
		svc = m_get_service_class((mbuf_t)pkt->pktsched_pkt);
		break;


	default:
		VERIFY(0);
		/* NOTREACHED */
	}

	return (svc);
}