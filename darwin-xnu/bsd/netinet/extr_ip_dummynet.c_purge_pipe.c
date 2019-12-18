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
struct dn_pipe {int /*<<< orphan*/  idle_heap; int /*<<< orphan*/  not_eligible_heap; int /*<<< orphan*/  scheduler_heap; struct mbuf* head; int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DN_FREE_PKT (struct mbuf*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  purge_flow_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
purge_pipe(struct dn_pipe *pipe)
{
    struct mbuf *m, *mnext;

    purge_flow_set( &(pipe->fs), 1 );

    mnext = pipe->head;
    while ((m = mnext) != NULL) {
	mnext = m->m_nextpkt;
	DN_FREE_PKT(m);
    }

    heap_free( &(pipe->scheduler_heap) );
    heap_free( &(pipe->not_eligible_heap) );
    heap_free( &(pipe->idle_heap) );
}