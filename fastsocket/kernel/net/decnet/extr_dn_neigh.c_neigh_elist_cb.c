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
struct neighbour {scalar_t__ dev; int nud_state; } ;
struct elist_cb_state {scalar_t__ dev; scalar_t__ t; scalar_t__ n; int* rs; int /*<<< orphan*/  ptr; } ;
struct dn_neigh {int flags; int priority; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int DN_NDFLAG_R1 ; 
 int DN_NDFLAG_R2 ; 
 int NUD_CONNECTED ; 
 int /*<<< orphan*/  dn_dn2eth (int*,int /*<<< orphan*/ ) ; 
 int* dn_find_slot (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void neigh_elist_cb(struct neighbour *neigh, void *_info)
{
	struct elist_cb_state *s = _info;
	struct dn_neigh *dn;

	if (neigh->dev != s->dev)
		return;

	dn = (struct dn_neigh *) neigh;
	if (!(dn->flags & (DN_NDFLAG_R1|DN_NDFLAG_R2)))
		return;

	if (s->t == s->n)
		s->rs = dn_find_slot(s->ptr, s->n, dn->priority);
	else
		s->t++;
	if (s->rs == NULL)
		return;

	dn_dn2eth(s->rs, dn->addr);
	s->rs += 6;
	*(s->rs) = neigh->nud_state & NUD_CONNECTED ? 0x80 : 0x0;
	*(s->rs) |= dn->priority;
	s->rs++;
}