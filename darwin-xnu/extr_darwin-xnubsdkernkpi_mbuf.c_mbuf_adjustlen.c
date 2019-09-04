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
struct TYPE_6__ {size_t m_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ mbuf_data (TYPE_1__*) ; 
 scalar_t__ mbuf_datastart (TYPE_1__*) ; 
 size_t mbuf_maxlen (TYPE_1__*) ; 

errno_t
mbuf_adjustlen(mbuf_t m, int amount)
{
	/* Verify m_len will be valid after adding amount */
	if (amount > 0) {
		int used = (size_t)mbuf_data(m) - (size_t)mbuf_datastart(m) +
		    m->m_len;

		if ((size_t)(amount + used) > mbuf_maxlen(m))
			return (EINVAL);
	} else if (-amount > m->m_len) {
		return (EINVAL);
	}

	m->m_len += amount;
	return (0);
}