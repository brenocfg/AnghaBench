#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mbuf {struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_DATA ; 
 struct mbuf* _M_RETRYHDR (int,int /*<<< orphan*/ ) ; 

struct mbuf *
m_getpackethdrs(int num_needed, int how)
{
	struct mbuf *m;
	struct mbuf **np, *top;

	top = NULL;
	np = &top;

	while (num_needed--) {
		m = _M_RETRYHDR(how, MT_DATA);
		if (m == NULL)
			break;

		*np = m;
		np = &m->m_nextpkt;
	}

	return (top);
}