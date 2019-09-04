#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int (* input ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ;} ;
struct TYPE_12__ {int (* input ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,char*) ;} ;
struct TYPE_14__ {TYPE_3__ v2; TYPE_2__ v1; } ;
struct if_proto {scalar_t__ proto_kpi; int /*<<< orphan*/  protocol_family; int /*<<< orphan*/  ifp; TYPE_4__ kpi; } ;
typedef  TYPE_5__* mbuf_t ;
struct TYPE_11__ {char* pkt_hdr; } ;
struct TYPE_15__ {TYPE_1__ m_pkthdr; struct TYPE_15__* m_nextpkt; } ;

/* Variables and functions */
 int EJUSTRETURN ; 
 scalar_t__ kProtoKPI_v1 ; 
 scalar_t__ kProtoKPI_v2 ; 
 int /*<<< orphan*/  m_freem (TYPE_5__*) ; 
 int /*<<< orphan*/  m_freem_list (TYPE_5__*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,char*) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static void
dlil_ifproto_input(struct if_proto * ifproto, mbuf_t m)
{
	int error;

	if (ifproto->proto_kpi == kProtoKPI_v1) {
		/* Version 1 protocols get one packet at a time */
		while (m != NULL) {
			char *	frame_header;
			mbuf_t	next_packet;

			next_packet = m->m_nextpkt;
			m->m_nextpkt = NULL;
			frame_header = m->m_pkthdr.pkt_hdr;
			m->m_pkthdr.pkt_hdr = NULL;
			error = (*ifproto->kpi.v1.input)(ifproto->ifp,
			    ifproto->protocol_family, m, frame_header);
			if (error != 0 && error != EJUSTRETURN)
				m_freem(m);
			m = next_packet;
		}
	} else if (ifproto->proto_kpi == kProtoKPI_v2) {
		/* Version 2 protocols support packet lists */
		error = (*ifproto->kpi.v2.input)(ifproto->ifp,
		    ifproto->protocol_family, m);
		if (error != 0 && error != EJUSTRETURN)
			m_freem_list(m);
	}
}