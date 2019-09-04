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
struct mbuf {scalar_t__ m_len; struct mbuf* m_next; } ;

/* Variables and functions */

__attribute__((used)) static int
m_space(struct mbuf *m)
{
	int space = 0;
	struct mbuf *nxt;

	for (nxt = m; nxt != NULL; nxt = nxt->m_next)
		space += nxt->m_len;

	return (space);
}