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
struct inbuf_t {int inputstate; int /*<<< orphan*/ * rcvbuf; struct bc_state* bcs; struct cardstate* cs; scalar_t__ tail; scalar_t__ head; } ;
struct cardstate {int dummy; } ;
struct bc_state {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void gigaset_inbuf_init(struct inbuf_t *inbuf, struct bc_state *bcs,
			       struct cardstate *cs, int inputstate)
/* inbuf->read must be allocated before! */
{
	inbuf->head = 0;
	inbuf->tail = 0;
	inbuf->cs = cs;
	inbuf->bcs = bcs; /*base driver: NULL*/
	inbuf->rcvbuf = NULL;
	inbuf->inputstate = inputstate;
}