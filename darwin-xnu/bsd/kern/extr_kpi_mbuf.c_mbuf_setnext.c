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
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_4__ {scalar_t__ m_type; struct TYPE_4__* m_next; int /*<<< orphan*/ * m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ MT_FREE ; 

errno_t
mbuf_setnext(mbuf_t mbuf, mbuf_t next)
{
	if (next && ((next)->m_nextpkt != NULL ||
	    (next)->m_type == MT_FREE))
		return (EINVAL);
	mbuf->m_next = next;

	return (0);
}