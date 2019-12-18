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
typedef  scalar_t__ u_int64_t ;
typedef  TYPE_2__* mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int pkt_flags; scalar_t__ pkt_timestamp; } ;
struct TYPE_5__ {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 int M_PKTHDR ; 
 int PKTF_TS_VALID ; 
 int /*<<< orphan*/  TRUE ; 

errno_t
mbuf_get_timestamp(mbuf_t m, u_int64_t *ts, boolean_t *valid)
{
	if (m == NULL || !(m->m_flags & M_PKTHDR) || ts == NULL)
		return (EINVAL);

	if ((m->m_pkthdr.pkt_flags & PKTF_TS_VALID) == 0) {
		if (valid != NULL)
			*valid = FALSE;
		*ts = 0;
	} else {
		if (valid != NULL)
			*valid = TRUE;
		*ts = m->m_pkthdr.pkt_timestamp;
	}
	return (0);
}