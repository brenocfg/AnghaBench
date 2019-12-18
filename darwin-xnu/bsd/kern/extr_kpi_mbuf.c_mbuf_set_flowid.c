#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  TYPE_2__* mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_5__ {int /*<<< orphan*/  drv_flowid; } ;
struct TYPE_6__ {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  driver_mtag_init (TYPE_2__*) ; 

errno_t
mbuf_set_flowid(mbuf_t m, u_int16_t flowid)
{
	if (m == NULL || !(m->m_flags & M_PKTHDR))
		return (EINVAL);

	driver_mtag_init(m);

	m->m_pkthdr.drv_flowid = flowid;

	return (0);
}