#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* mbuf_t ;
struct TYPE_8__ {int /*<<< orphan*/  buf_sndbuf; int /*<<< orphan*/  buf_interface; } ;
typedef  TYPE_3__ mbuf_buffer_status_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_6__ {int pkt_flags; int /*<<< orphan*/  bufstatus_sndbuf; int /*<<< orphan*/  bufstatus_if; } ;
struct TYPE_7__ {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int M_PKTHDR ; 
 int PKTF_VALID_UNSENT_DATA ; 

errno_t
mbuf_get_buffer_status(const mbuf_t m, mbuf_buffer_status_t *buf_status)
{
	if (m == NULL || buf_status == NULL || !(m->m_flags & M_PKTHDR) ||
	    !(m->m_pkthdr.pkt_flags & PKTF_VALID_UNSENT_DATA))
		return (EINVAL);

	buf_status->buf_interface = m->m_pkthdr.bufstatus_if;
	buf_status->buf_sndbuf = m->m_pkthdr.bufstatus_sndbuf;
	return (0);
}