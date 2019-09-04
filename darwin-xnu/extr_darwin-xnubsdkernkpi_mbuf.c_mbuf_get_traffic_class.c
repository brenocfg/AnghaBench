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
typedef  int /*<<< orphan*/  mbuf_traffic_class_t ;
typedef  TYPE_1__* mbuf_t ;
struct TYPE_4__ {int m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_TC_BE ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  m_get_traffic_class (TYPE_1__*) ; 

mbuf_traffic_class_t
mbuf_get_traffic_class(mbuf_t m)
{
	if (m == NULL || !(m->m_flags & M_PKTHDR))
		return (MBUF_TC_BE);

	return (m_get_traffic_class(m));
}