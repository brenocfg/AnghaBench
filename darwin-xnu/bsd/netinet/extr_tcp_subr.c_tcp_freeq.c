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
struct tseg_qent {int /*<<< orphan*/  tqe_m; } ;
struct tcpcb {scalar_t__ t_reassqlen; int /*<<< orphan*/  t_segq; } ;

/* Variables and functions */
 struct tseg_qent* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct tseg_qent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_reass_zone ; 
 int /*<<< orphan*/  tqe_q ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct tseg_qent*) ; 

int
tcp_freeq(struct tcpcb *tp)
{
	struct tseg_qent *q;
	int rv = 0;

	while ((q = LIST_FIRST(&tp->t_segq)) != NULL) {
		LIST_REMOVE(q, tqe_q);
		m_freem(q->tqe_m);
		zfree(tcp_reass_zone, q);
		rv = 1;
	}
	tp->t_reassqlen = 0;
	return (rv);
}