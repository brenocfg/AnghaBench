#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_5__* Type ;
struct TYPE_19__ {int /*<<< orphan*/  outofline; int /*<<< orphan*/  align; int /*<<< orphan*/  size; } ;
struct TYPE_14__ {int i; int u; int /*<<< orphan*/  d; } ;
struct TYPE_13__ {int /*<<< orphan*/  d; int /*<<< orphan*/  u; int /*<<< orphan*/  i; } ;
struct TYPE_15__ {TYPE_2__ max; TYPE_1__ min; } ;
struct TYPE_16__ {TYPE_3__ limits; } ;
struct TYPE_18__ {TYPE_4__ u; int /*<<< orphan*/  addressed; TYPE_5__* type; } ;
struct TYPE_17__ {int align; int size; int op; } ;
typedef  TYPE_6__* Symbol ;
typedef  TYPE_7__ Metrics ;

/* Variables and functions */
 int /*<<< orphan*/  DBL_MAX ; 
#define  FLOAT 130 
 int /*<<< orphan*/  FLT_MAX ; 
 int /*<<< orphan*/  GLOBAL ; 
#define  INT 129 
 int /*<<< orphan*/  LDBL_MAX ; 
 int /*<<< orphan*/  PERM ; 
#define  UNSIGNED 128 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_6__* install (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ones (int) ; 
 int /*<<< orphan*/  string (char*) ; 
 TYPE_5__* type (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  types ; 

__attribute__((used)) static Type xxinit(int op, char *name, Metrics m) {
	Symbol p = install(string(name), &types, GLOBAL, PERM);
	Type ty = type(op, 0, m.size, m.align, p);

	assert(ty->align == 0 || ty->size%ty->align == 0);
	p->type = ty;
	p->addressed = m.outofline;
	switch (ty->op) {
	case INT:
		p->u.limits.max.i = ones(8*ty->size)>>1;
		p->u.limits.min.i = -p->u.limits.max.i - 1;
		break;
	case UNSIGNED:
		p->u.limits.max.u = ones(8*ty->size);
		p->u.limits.min.u = 0;
		break;
	case FLOAT:
		if (ty->size == sizeof (float))
			p->u.limits.max.d =  FLT_MAX;
		else if (ty->size == sizeof (double))
			p->u.limits.max.d =  DBL_MAX;
		else
			p->u.limits.max.d = LDBL_MAX;
		p->u.limits.min.d = -p->u.limits.max.d;
		break;
	default: assert(0);
	}
	return ty;
}