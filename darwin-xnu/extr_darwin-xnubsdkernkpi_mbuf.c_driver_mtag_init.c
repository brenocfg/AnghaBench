#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* mbuf_t ;
struct TYPE_4__ {int pkt_flags; int /*<<< orphan*/  driver_mtag; } ;
struct TYPE_5__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int PKTF_DRIVER_MTAG ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
driver_mtag_init(mbuf_t m)
{
	if ((m->m_pkthdr.pkt_flags & PKTF_DRIVER_MTAG) == 0) {
		m->m_pkthdr.pkt_flags |= PKTF_DRIVER_MTAG;
		bzero(&m->m_pkthdr.driver_mtag,
		    sizeof(m->m_pkthdr.driver_mtag));
	}
}