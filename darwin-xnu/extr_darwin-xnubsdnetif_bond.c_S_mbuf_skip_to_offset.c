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
struct mbuf {int m_len; struct mbuf* m_next; } ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static struct mbuf *
S_mbuf_skip_to_offset(struct mbuf * m, int32_t * offset)
{
    int			len;

    len = m->m_len;
    while (*offset >= len) {
	*offset -= len;
	m = m->m_next;
	if (m == NULL) {
	    break;
	}
	len = m->m_len;
    }
    return (m);
}