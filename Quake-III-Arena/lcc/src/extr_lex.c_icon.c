#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {unsigned long i; unsigned long u; } ;
struct TYPE_22__ {TYPE_6__ v; } ;
struct TYPE_23__ {TYPE_7__ c; } ;
struct TYPE_24__ {TYPE_8__ u; TYPE_10__* type; } ;
struct TYPE_20__ {TYPE_4__* sym; } ;
struct TYPE_16__ {unsigned long i; unsigned long u; } ;
struct TYPE_17__ {TYPE_1__ max; } ;
struct TYPE_18__ {TYPE_2__ limits; } ;
struct TYPE_19__ {TYPE_3__ u; } ;
struct TYPE_15__ {int op; TYPE_5__ u; } ;
typedef  TYPE_9__* Symbol ;

/* Variables and functions */
#define  INT 129 
#define  UNSIGNED 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 unsigned char* cp ; 
 TYPE_10__* inttype ; 
 TYPE_10__* longtype ; 
 int /*<<< orphan*/  ppnumber (char*) ; 
 int /*<<< orphan*/  token ; 
 TYPE_9__ tval ; 
 void* unsignedlong ; 
 TYPE_10__* unsignedtype ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static Symbol icon(unsigned long n, int overflow, int base) {
	if ((*cp=='u'||*cp=='U') && (cp[1]=='l'||cp[1]=='L')
	||  (*cp=='l'||*cp=='L') && (cp[1]=='u'||cp[1]=='U')) {
		tval.type = unsignedlong;
		cp += 2;
	} else if (*cp == 'u' || *cp == 'U') {
		if (overflow || n > unsignedtype->u.sym->u.limits.max.i)
			tval.type = unsignedlong;
		else
			tval.type = unsignedtype;
		cp += 1;
	} else if (*cp == 'l' || *cp == 'L') {
		if (overflow || n > longtype->u.sym->u.limits.max.i)
			tval.type = unsignedlong;
		else
			tval.type = longtype;
		cp += 1;
	} else if (overflow || n > longtype->u.sym->u.limits.max.i)
		tval.type = unsignedlong;
	else if (n > inttype->u.sym->u.limits.max.i)
		tval.type = longtype;
	else if (base != 10 && n > inttype->u.sym->u.limits.max.i)
		tval.type = unsignedtype;
	else
		tval.type = inttype;
	switch (tval.type->op) {
	case INT:
		if (overflow || n > tval.type->u.sym->u.limits.max.i) {
			warning("overflow in constant `%S'\n", token,
				(char*)cp - token);
			tval.u.c.v.i = tval.type->u.sym->u.limits.max.i;
		} else
			tval.u.c.v.i = n;
		break;
	case UNSIGNED:
		if (overflow || n > tval.type->u.sym->u.limits.max.u) {
			warning("overflow in constant `%S'\n", token,
				(char*)cp - token);
			tval.u.c.v.u = tval.type->u.sym->u.limits.max.u;
		} else
			tval.u.c.v.u = n;
		break;
	default: assert(0);
	}
	ppnumber("integer");
	return &tval;
}