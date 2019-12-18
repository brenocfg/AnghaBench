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
typedef  TYPE_1__* mbuf_t ;
typedef  int /*<<< orphan*/  mbuf_svc_class_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {int m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  m_set_service_class (TYPE_1__*,int /*<<< orphan*/ ) ; 

errno_t
mbuf_set_service_class(mbuf_t m, mbuf_svc_class_t sc)
{
	if (m == NULL || !(m->m_flags & M_PKTHDR))
		return (EINVAL);

	return (m_set_service_class(m, sc));
}