#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* Type ;
typedef  TYPE_2__* Tree ;
struct TYPE_35__ {int /*<<< orphan*/  type; } ;
struct TYPE_34__ {int /*<<< orphan*/  op; TYPE_4__* type; } ;
struct TYPE_33__ {long size; TYPE_4__* type; } ;

/* Variables and functions */
 int ADD ; 
 int /*<<< orphan*/  MUL ; 
 scalar_t__ YYcheck ; 
 TYPE_1__* binary (TYPE_4__*,TYPE_4__*) ; 
 TYPE_2__* cast (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  cnsttree (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  error (char*,TYPE_4__*) ; 
 TYPE_1__* inttype ; 
 int /*<<< orphan*/  isaddrop (int /*<<< orphan*/ ) ; 
 scalar_t__ isarith (TYPE_4__*) ; 
 int /*<<< orphan*/  isfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ isint (TYPE_4__*) ; 
 scalar_t__ isptr (TYPE_4__*) ; 
 TYPE_2__* multree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* nullcall (TYPE_1__*,scalar_t__,TYPE_2__*,TYPE_2__*) ; 
 TYPE_1__* promote (TYPE_4__*) ; 
 int /*<<< orphan*/  signedptr ; 
 TYPE_2__* simplify (int,TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  typeerror (int,TYPE_2__*,TYPE_2__*) ; 
 TYPE_1__* unqual (TYPE_4__*) ; 

__attribute__((used)) static Tree addtree(int op, Tree l, Tree r) {
	Type ty = inttype;

	if (isarith(l->type) && isarith(r->type)) {
		ty = binary(l->type, r->type);
		l = cast(l, ty);
		r = cast(r, ty);		
	} else if (isptr(l->type) && isint(r->type))
		return addtree(ADD, r, l);
	else if (  isptr(r->type) && isint(l->type)
	&& !isfunc(r->type->type))
		{
			long n;
			ty = unqual(r->type);
			n = unqual(ty->type)->size;
			if (n == 0)
				error("unknown size for type `%t'\n", ty->type);
			l = cast(l, promote(l->type));
			if (n > 1)
				l = multree(MUL, cnsttree(signedptr, n), l);
			if (YYcheck && !isaddrop(r->op))		/* omit */
				return nullcall(ty, YYcheck, r, l);	/* omit */
			return simplify(ADD, ty, l, r);
		}

	else
		typeerror(op, l, r);
	return simplify(op, ty, l, r);
}