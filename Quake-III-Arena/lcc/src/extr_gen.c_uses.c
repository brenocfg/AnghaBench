#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_10__** kids; } ;
struct TYPE_18__ {TYPE_5__ x; } ;
struct TYPE_17__ {scalar_t__ set; int mask; } ;
struct TYPE_14__ {TYPE_2__* regnode; } ;
struct TYPE_15__ {TYPE_3__ x; } ;
struct TYPE_13__ {scalar_t__ set; int mask; } ;
struct TYPE_12__ {scalar_t__ registered; } ;
struct TYPE_11__ {TYPE_4__** syms; TYPE_1__ x; } ;
typedef  TYPE_6__* Regnode ;
typedef  TYPE_7__* Node ;

/* Variables and functions */
 int NELEMS (TYPE_10__**) ; 
 size_t RX ; 

__attribute__((used)) static int uses(Node p, Regnode rn) {
	int i;

	for (i = 0; i < NELEMS(p->x.kids); i++)
		if (
			p->x.kids[i] &&
			p->x.kids[i]->x.registered &&
			rn->set == p->x.kids[i]->syms[RX]->x.regnode->set &&
			(rn->mask&p->x.kids[i]->syms[RX]->x.regnode->mask)
		)
			return 1;
	return 0;
}