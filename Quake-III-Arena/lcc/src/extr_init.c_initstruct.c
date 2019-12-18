#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  TYPE_5__* Type ;
struct TYPE_19__ {int align; scalar_t__ size; } ;
struct TYPE_18__ {int offset; TYPE_8__* type; struct TYPE_18__* link; scalar_t__ lsb; } ;
struct TYPE_16__ {TYPE_3__* sym; } ;
struct TYPE_17__ {int align; TYPE_4__ u; } ;
struct TYPE_13__ {TYPE_6__* flist; } ;
struct TYPE_14__ {TYPE_1__ s; } ;
struct TYPE_15__ {TYPE_2__ u; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* space ) (int) ;} ;
typedef  TYPE_6__* Field ;

/* Variables and functions */
 TYPE_11__* IR ; 
 char gettok () ; 
 scalar_t__ initfields (TYPE_6__*,TYPE_6__*) ; 
 int /*<<< orphan*/  initializer (TYPE_8__*,int) ; 
 int roundup (int,int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 char t ; 

__attribute__((used)) static int initstruct(int len, Type ty, int lev) {
	int a, n = 0;
	Field p = ty->u.sym->u.s.flist;

	do {
		if (p->offset > n) {
			(*IR->space)(p->offset - n);
			n += p->offset - n;
		}
		if (p->lsb) {
			Field q = p;
			while (q->link && q->link->offset == p->offset)
				q = q->link;
			n += initfields(p, q->link);
			p = q;
		} else {
			initializer(p->type, lev);
			n += p->type->size;
		}
		if (p->link) {
			p = p->link;
			a = p->type->align;
		} else
			a = ty->align;
		if (a && n%a) {
			(*IR->space)(a - n%a);
			n = roundup(n, a);
		}
		if (len > 0 && n >= len || t != ',')
			break;
		t = gettok();
	} while (t != '}');
	return n;
}