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
typedef  int /*<<< orphan*/ * mbuf_tx_compl_func ;
typedef  TYPE_2__* mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int pkt_flags; int pkt_compl_callbacks; uintptr_t pkt_compl_context; } ;
struct TYPE_5__ {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  OSIncrementAtomic64 (int /*<<< orphan*/ *) ; 
 int PKTF_TX_COMPL_TS_REQ ; 
 size_t UINT32_MAX ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 uintptr_t atomic_add_32_ov (int /*<<< orphan*/ *,int) ; 
 size_t get_tx_compl_callback_index (int /*<<< orphan*/ *) ; 
 scalar_t__ mbuf_tx_compl_debug ; 
 int /*<<< orphan*/  mbuf_tx_compl_index ; 
 int /*<<< orphan*/  mbuf_tx_compl_outstanding ; 

errno_t
mbuf_set_timestamp_requested(mbuf_t m, uintptr_t *pktid,
    mbuf_tx_compl_func callback)
{
	size_t i;

	if (m == NULL || !(m->m_flags & M_PKTHDR) || callback == NULL ||
	    pktid == NULL)
		return (EINVAL);

	i = get_tx_compl_callback_index(callback);
	if (i == UINT32_MAX)
		return (ENOENT);

#if (DEBUG || DEVELOPMENT)
	VERIFY(i < sizeof(m->m_pkthdr.pkt_compl_callbacks));
#endif /* (DEBUG || DEVELOPMENT) */

	if ((m->m_pkthdr.pkt_flags & PKTF_TX_COMPL_TS_REQ) == 0) {
		m->m_pkthdr.pkt_compl_callbacks = 0;
		m->m_pkthdr.pkt_flags |= PKTF_TX_COMPL_TS_REQ;
		m->m_pkthdr.pkt_compl_context =
		    atomic_add_32_ov(&mbuf_tx_compl_index, 1);

#if (DEBUG || DEVELOPMENT)
		if (mbuf_tx_compl_debug != 0) {
			OSIncrementAtomic64(&mbuf_tx_compl_outstanding);
		}
#endif /* (DEBUG || DEVELOPMENT) */
	}
	m->m_pkthdr.pkt_compl_callbacks |= (1 << i);
	*pktid = m->m_pkthdr.pkt_compl_context;

	return (0);
}