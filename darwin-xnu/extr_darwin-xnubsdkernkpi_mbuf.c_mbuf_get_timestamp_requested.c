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
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int pkt_flags; } ;
struct TYPE_5__ {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int M_PKTHDR ; 
 int PKTF_TX_COMPL_TS_REQ ; 
 int /*<<< orphan*/  TRUE ; 

errno_t
mbuf_get_timestamp_requested(mbuf_t m, boolean_t *requested)
{
	if (m == NULL || !(m->m_flags & M_PKTHDR))
		return (EINVAL);

	if ((m->m_pkthdr.pkt_flags & PKTF_TX_COMPL_TS_REQ) == 0) {
		*requested = FALSE;
	} else {
		*requested = TRUE;
	}
	return (0);
}