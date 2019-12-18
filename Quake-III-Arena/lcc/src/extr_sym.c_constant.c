#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_19__ ;
typedef  struct TYPE_20__   TYPE_15__ ;

/* Type definitions */
struct TYPE_26__ {int u; } ;
struct TYPE_22__ {TYPE_5__ v; } ;
struct TYPE_23__ {TYPE_1__ c; } ;
struct TYPE_28__ {int defined; struct TYPE_28__* up; TYPE_2__ u; int /*<<< orphan*/  sclass; TYPE_6__* type; int /*<<< orphan*/  scope; int /*<<< orphan*/  name; } ;
struct entry {TYPE_7__ sym; struct entry* link; } ;
typedef  TYPE_5__ Value ;
typedef  TYPE_6__* Type ;
struct TYPE_25__ {TYPE_3__* sym; } ;
struct TYPE_27__ {int op; TYPE_4__ u; } ;
struct TYPE_24__ {int /*<<< orphan*/  addressed; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* defsymbol ) (TYPE_7__*) ;} ;
struct TYPE_20__ {struct entry** buckets; TYPE_7__* all; } ;
typedef  TYPE_7__* Symbol ;

/* Variables and functions */
#define  ARRAY 133 
 int /*<<< orphan*/  CONSTANTS ; 
#define  FLOAT 132 
#define  FUNCTION 131 
 int HASHSIZE ; 
#define  INT 130 
 TYPE_19__* IR ; 
 int /*<<< orphan*/  NEW0 (struct entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PERM ; 
#define  POINTER 129 
 int /*<<< orphan*/  STATIC ; 
#define  UNSIGNED 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_15__* constants ; 
 struct entry* d ; 
 scalar_t__ eqtype (TYPE_6__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  equalp (struct entry*) ; 
 struct entry* g ; 
 struct entry* i ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 
 struct entry* u ; 
 TYPE_6__* unqual (TYPE_6__*) ; 
 int /*<<< orphan*/  vtoa (TYPE_6__*,TYPE_5__) ; 

Symbol constant(Type ty, Value v) {
	struct entry *p;
	unsigned h = v.u&(HASHSIZE-1);

	ty = unqual(ty);
	for (p = constants->buckets[h]; p; p = p->link)
		if (eqtype(ty, p->sym.type, 1))
			switch (ty->op) {
			case INT:      if (equalp(i)) return &p->sym; break;
			case UNSIGNED: if (equalp(u)) return &p->sym; break;
			case FLOAT:    if (equalp(d)) return &p->sym; break;
			case FUNCTION: if (equalp(g)) return &p->sym; break;
			case ARRAY:
			case POINTER:  if (equalp(p)) return &p->sym; break;
			default: assert(0);
			}
	NEW0(p, PERM);
	p->sym.name = vtoa(ty, v);
	p->sym.scope = CONSTANTS;
	p->sym.type = ty;
	p->sym.sclass = STATIC;
	p->sym.u.c.v = v;
	p->link = constants->buckets[h];
	p->sym.up = constants->all;
	constants->all = &p->sym;
	constants->buckets[h] = p;
	if (ty->u.sym && !ty->u.sym->addressed)
		(*IR->defsymbol)(&p->sym);
	p->sym.defined = 1;
	return &p->sym;
}