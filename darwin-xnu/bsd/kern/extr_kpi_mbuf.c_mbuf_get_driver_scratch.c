#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  TYPE_1__* mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int M_PKTHDR ; 
 size_t m_scratch_get (TYPE_1__*,int /*<<< orphan*/ **) ; 

errno_t
mbuf_get_driver_scratch(mbuf_t m, u_int8_t **area, size_t *area_len)
{
	if (m == NULL || area == NULL || area_len == NULL ||
	    !(m->m_flags & M_PKTHDR))
		return (EINVAL);

	*area_len = m_scratch_get(m, area);
	return (0);
}