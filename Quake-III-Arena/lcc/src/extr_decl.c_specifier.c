#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* Type ;
struct TYPE_30__ {TYPE_2__* type; } ;
struct TYPE_29__ {TYPE_1__* type; int /*<<< orphan*/  size; } ;
struct TYPE_28__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
#define  AUTO 147 
 int Aflag ; 
#define  CHAR 146 
#define  CONST 145 
#define  DOUBLE 144 
#define  ENUM 143 
#define  EXTERN 142 
#define  FLOAT 141 
 int /*<<< orphan*/  GLOBAL ; 
#define  ID 140 
#define  INT 139 
#define  LONG 138 
#define  REGISTER 137 
#define  SHORT 136 
#define  SIGNED 135 
#define  STATIC 134 
#define  STRUCT 133 
#define  TYPEDEF 132 
#define  UNION 131 
#define  UNSIGNED 130 
#define  VOID 129 
#define  VOLATILE 128 
 TYPE_2__* enumdcl () ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int gettok () ; 
 TYPE_2__* inttype ; 
 int /*<<< orphan*/  isconst (TYPE_2__*) ; 
 int /*<<< orphan*/  isqual (TYPE_2__*) ; 
 int /*<<< orphan*/  istypename (int,TYPE_4__*) ; 
 int /*<<< orphan*/  isvolatile (TYPE_2__*) ; 
 int /*<<< orphan*/  level ; 
 TYPE_2__* longdouble ; 
 TYPE_2__* longlong ; 
 TYPE_2__* longtype ; 
 TYPE_2__* qual (int const,TYPE_2__*) ; 
 TYPE_2__* shorttype ; 
 TYPE_2__* signedchar ; 
 int /*<<< orphan*/  src ; 
 TYPE_2__* structdcl (int) ; 
 int t ; 
 TYPE_4__* tsym ; 
 TYPE_2__* unqual (TYPE_2__*) ; 
 TYPE_2__* unsignedchar ; 
 TYPE_2__* unsignedlong ; 
 TYPE_2__* unsignedlonglong ; 
 TYPE_2__* unsignedshort ; 
 TYPE_2__* unsignedtype ; 
 int /*<<< orphan*/  use (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,TYPE_2__*) ; 

__attribute__((used)) static Type specifier(int *sclass) {
	int cls, cons, sign, size, type, vol;
	Type ty = NULL;

	cls = vol = cons = sign = size = type = 0;
	if (sclass == NULL)
		cls = AUTO;
	for (;;) {
		int *p, tt = t;
		switch (t) {
		case AUTO:
		case REGISTER: if (level <= GLOBAL && cls == 0)
		               	error("invalid use of `%k'\n", t);
		               p = &cls;  t = gettok();      break;
		case STATIC: case EXTERN:
		case TYPEDEF:  p = &cls;  t = gettok();      break;
		case CONST:    p = &cons; t = gettok();      break;
		case VOLATILE: p = &vol;  t = gettok();      break;
		case SIGNED:
		case UNSIGNED: p = &sign; t = gettok();      break;
		case LONG:     if (size == LONG) {
		                       size = 0;
		                       tt = LONG+LONG;
		               }
		               p = &size; t = gettok();      break;
		case SHORT:    p = &size; t = gettok();      break;
		case VOID: case CHAR: case INT: case FLOAT:
		case DOUBLE:   p = &type; ty = tsym->type;
		                          t = gettok();      break;
		case ENUM:     p = &type; ty = enumdcl();    break;
		case STRUCT:
		case UNION:    p = &type; ty = structdcl(t); break;
		case ID:
			if (istypename(t, tsym) && type == 0
			&& sign == 0 && size == 0) {
				use(tsym, src);
				ty = tsym->type;
				if (isqual(ty)
				&& ty->size != ty->type->size) {
					ty = unqual(ty);
					if (isconst(tsym->type))
						ty = qual(CONST, ty);
					if (isvolatile(tsym->type))
						ty = qual(VOLATILE, ty);
					tsym->type = ty;
				}
				p = &type;
				t = gettok();
			} else
				p = NULL;
			break;
		default: p = NULL;
		}
		if (p == NULL)
			break;
		if (*p)
			error("invalid use of `%k'\n", tt);
		*p = tt;
	}
	if (sclass)
		*sclass = cls;
	if (type == 0) {
		type = INT;
		ty = inttype;
	}
	if (size == SHORT     && type != INT
	||  size == LONG+LONG && type != INT
	||  size == LONG      && type != INT && type != DOUBLE
	||  sign && type != INT && type != CHAR)
		error("invalid type specification\n");
	if (type == CHAR && sign)
		ty = sign == UNSIGNED ? unsignedchar : signedchar;
	else if (size == SHORT)
		ty = sign == UNSIGNED ? unsignedshort : shorttype;
	else if (size == LONG && type == DOUBLE)
		ty = longdouble;
	else if (size == LONG+LONG) {
		ty = sign == UNSIGNED ? unsignedlonglong : longlong;
		if (Aflag >= 1)
			warning("`%t' is a non-ANSI type\n", ty);
	} else if (size == LONG)
		ty = sign == UNSIGNED ? unsignedlong : longtype;
	else if (sign == UNSIGNED && type == INT)
		ty = unsignedtype;
	if (cons == CONST)
		ty = qual(CONST, ty);
	if (vol  == VOLATILE)
		ty = qual(VOLATILE, ty);
	return ty;
}