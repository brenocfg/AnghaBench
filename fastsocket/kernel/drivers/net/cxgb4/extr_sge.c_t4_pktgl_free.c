#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pkt_gl {int nfrags; TYPE_1__* frags; } ;
struct TYPE_2__ {int /*<<< orphan*/  page; } ;
typedef  TYPE_1__ skb_frag_t ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void t4_pktgl_free(const struct pkt_gl *gl)
{
	int n;
	const skb_frag_t *p;

	for (p = gl->frags, n = gl->nfrags - 1; n--; p++)
		put_page(p->page);
}