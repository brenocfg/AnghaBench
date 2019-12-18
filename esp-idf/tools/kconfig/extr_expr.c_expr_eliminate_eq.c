#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct expr {int dummy; } ;
struct TYPE_5__ {int type; } ;

/* Variables and functions */
#define  E_AND 129 
#define  E_OR 128 
 int /*<<< orphan*/  __expr_eliminate_eq (int,struct expr**,struct expr**) ; 
 TYPE_1__* e1 ; 
 TYPE_1__* e2 ; 
 TYPE_1__* expr_eliminate_yn (TYPE_1__*) ; 

void expr_eliminate_eq(struct expr **ep1, struct expr **ep2)
{
	if (!e1 || !e2)
		return;
	switch (e1->type) {
	case E_OR:
	case E_AND:
		__expr_eliminate_eq(e1->type, ep1, ep2);
	default:
		;
	}
	if (e1->type != e2->type) switch (e2->type) {
	case E_OR:
	case E_AND:
		__expr_eliminate_eq(e2->type, ep1, ep2);
	default:
		;
	}
	e1 = expr_eliminate_yn(e1);
	e2 = expr_eliminate_yn(e2);
}