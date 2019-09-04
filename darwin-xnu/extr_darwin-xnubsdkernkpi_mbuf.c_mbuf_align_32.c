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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  TYPE_1__* mbuf_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_6__ {int m_flags; size_t m_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTSUP ; 
 int M_EXT ; 
 scalar_t__ m_mclhasreference (TYPE_1__*) ; 
 size_t mbuf_datastart (TYPE_1__*) ; 
 size_t mbuf_trailingspace (TYPE_1__*) ; 

errno_t
mbuf_align_32(mbuf_t mbuf, size_t len)
{
	if ((mbuf->m_flags & M_EXT) != 0 && m_mclhasreference(mbuf))
		return (ENOTSUP);
	mbuf->m_data = mbuf_datastart(mbuf);
	mbuf->m_data +=
	    ((mbuf_trailingspace(mbuf) - len) &~ (sizeof(u_int32_t) - 1));

	return (0);
}