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
struct dn_pkt_tag {scalar_t__ dn_output_time; } ;
struct dn_pipe {struct mbuf* tail; struct mbuf* head; scalar_t__ delay; } ;
struct dn_flow_queue {int len_bytes; int /*<<< orphan*/  len; struct mbuf* head; } ;

/* Variables and functions */
 scalar_t__ curr_time ; 
 struct dn_pkt_tag* dn_tag_get (struct mbuf*) ; 

__attribute__((used)) static void
move_pkt(struct mbuf *pkt, struct dn_flow_queue *q,
	struct dn_pipe *p, int len)
{
    struct dn_pkt_tag *dt = dn_tag_get(pkt);

    q->head = pkt->m_nextpkt ;
    q->len-- ;
    q->len_bytes -= len ;

    dt->dn_output_time = curr_time + p->delay ;

    if (p->head == NULL)
	p->head = pkt;
    else
	p->tail->m_nextpkt = pkt;
    p->tail = pkt;
    p->tail->m_nextpkt = NULL;
}