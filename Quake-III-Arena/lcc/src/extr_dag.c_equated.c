#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* equatedto; } ;
struct TYPE_7__ {TYPE_1__ l; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
typedef  TYPE_3__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static Symbol equated(Symbol p) {
	{ Symbol q; for (q = p->u.l.equatedto; q; q = q->u.l.equatedto) assert(p != q); }
	while (p->u.l.equatedto)
		p = p->u.l.equatedto;
	return p;
}