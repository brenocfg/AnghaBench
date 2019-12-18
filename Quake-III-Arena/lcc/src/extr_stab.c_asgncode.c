#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* Type ;
struct TYPE_14__ {TYPE_4__* type; struct TYPE_14__* link; } ;
struct TYPE_12__ {TYPE_2__* sym; } ;
struct TYPE_10__ {int marked; scalar_t__ typeno; } ;
struct TYPE_13__ {int op; TYPE_3__ u; TYPE_1__ x; struct TYPE_13__* type; } ;
struct TYPE_11__ {char* name; } ;
typedef  TYPE_5__* Field ;

/* Variables and functions */
#define  ARRAY 139 
#define  CONST 138 
#define  ENUM 137 
#define  FLOAT 136 
#define  FUNCTION 135 
#define  INT 134 
#define  POINTER 133 
#define  STRUCT 132 
#define  UNION 131 
#define  UNSIGNED 130 
#define  VOID 129 
#define  VOLATILE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbxout (TYPE_4__*) ; 
 TYPE_5__* fieldlist (TYPE_4__*) ; 
 scalar_t__ ntypes ; 

__attribute__((used)) static void asgncode(Type ty, int lev) {
	if (ty->x.marked || ty->x.typeno)
		return;
	ty->x.marked = 1;
	switch (ty->op) {
	case VOLATILE: case CONST: case VOLATILE+CONST:
		asgncode(ty->type, lev);
		ty->x.typeno = ty->type->x.typeno;
		break;
	case POINTER: case FUNCTION: case ARRAY:
		asgncode(ty->type, lev + 1);
		/* fall thru */
	case VOID: case INT: case UNSIGNED: case FLOAT:
		break;
	case STRUCT: case UNION: {
		Field p;
		for (p = fieldlist(ty); p; p = p->link)
			asgncode(p->type, lev + 1);
		/* fall thru */
	case ENUM:
		if (ty->x.typeno == 0)
			ty->x.typeno = ++ntypes;
		if (lev > 0 && (*ty->u.sym->name < '0' || *ty->u.sym->name > '9'))
			dbxout(ty);
		break;
		}
	default:
		assert(0);
	}
}