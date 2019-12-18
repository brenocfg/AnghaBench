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
struct mbuf {int m_flags; struct mbuf* m_next; } ;

/* Variables and functions */
 int M_PKTHDR ; 

__attribute__((used)) static struct mbuf *
cfil_data_start(struct mbuf *m)
{
	struct mbuf *m0;

	// Locate the start of data
	for (m0 = m; m0 != NULL; m0 = m0->m_next) {
		if (m0->m_flags & M_PKTHDR)
			break;
	}
	return m0;
}