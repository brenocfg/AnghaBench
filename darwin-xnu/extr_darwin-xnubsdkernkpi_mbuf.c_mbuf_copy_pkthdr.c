#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_6__ {int m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  m_copy_pkthdr (TYPE_1__*,TYPE_1__* const) ; 

errno_t
mbuf_copy_pkthdr(mbuf_t dest, const mbuf_t src)
{
	if (((src)->m_flags & M_PKTHDR) == 0)
		return (EINVAL);

	m_copy_pkthdr(dest, src);

	return (0);
}