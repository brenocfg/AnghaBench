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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct mbuf {struct mbuf* m_next; int /*<<< orphan*/  m_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mbuf_data (struct mbuf*) ; 
 scalar_t__ min (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
bpf_mcopy(struct mbuf * m, void *dst_arg, size_t len)
{
	u_int count;
	u_char *dst;

	dst = dst_arg;
	while (len > 0) {
		if (m == 0)
			panic("bpf_mcopy");
		count = min(m->m_len, len);
		bcopy(mbuf_data(m), dst, count);
		m = m->m_next;
		dst += count;
		len -= count;
	}
}