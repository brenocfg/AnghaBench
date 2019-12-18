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
typedef  scalar_t__ kern_return_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int pkt_flags; scalar_t__ drv_tx_status; } ;
struct TYPE_5__ {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int M_PKTHDR ; 
 int PKTF_DRIVER_MTAG ; 

errno_t
mbuf_get_status(mbuf_t m, kern_return_t *status)
{
	if (m == NULL || !(m->m_flags & M_PKTHDR) || status == NULL)
		return (EINVAL);

	if ((m->m_pkthdr.pkt_flags & PKTF_DRIVER_MTAG) == 0) {
		*status = 0;
	} else {
		*status = m->m_pkthdr.drv_tx_status;
	}
	return (0);
}