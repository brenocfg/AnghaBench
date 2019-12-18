#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  TYPE_3__* Type ;
struct TYPE_18__ {char* name; } ;
struct TYPE_15__ {TYPE_3__** proto; } ;
struct TYPE_16__ {TYPE_1__ f; TYPE_13__* sym; } ;
struct TYPE_17__ {int op; int size; struct TYPE_17__* type; TYPE_2__ u; } ;
struct TYPE_14__ {char* name; } ;
typedef  TYPE_4__* Symbol ;

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
 int /*<<< orphan*/  assert (TYPE_13__*) ; 
 TYPE_4__* findtype (TYPE_3__*) ; 
 int /*<<< orphan*/  isarray (TYPE_3__*) ; 
 int /*<<< orphan*/  ischar (TYPE_3__*) ; 
 int /*<<< orphan*/  isfunc (TYPE_3__*) ; 
 int /*<<< orphan*/  isptr (TYPE_3__*) ; 
 char* stringf (char*,...) ; 
 TYPE_3__* voidtype ; 
 int /*<<< orphan*/  warning (char*,int) ; 

char *typestring(Type ty, char *str) {
	for ( ; ty; ty = ty->type) {
		Symbol p;
		switch (ty->op) {
		case CONST+VOLATILE: case CONST: case VOLATILE:
			if (isptr(ty->type))
				str = stringf("%k %s", ty->op, str);
			else
				return stringf("%k %s", ty->op, typestring(ty->type, str));
			break;
		case STRUCT: case UNION: case ENUM:
			assert(ty->u.sym);
			if ((p = findtype(ty)) != NULL)
				return *str ? stringf("%s %s", p->name, str) : p->name;
			if (*ty->u.sym->name >= '1' && *ty->u.sym->name <= '9')
				warning("unnamed %k in prototype\n", ty->op);
			if (*str)
				return stringf("%k %s %s", ty->op, ty->u.sym->name, str);
			else
				return stringf("%k %s", ty->op, ty->u.sym->name);
		case VOID: case FLOAT: case INT: case UNSIGNED:
			return *str ? stringf("%s %s", ty->u.sym->name, str) : ty->u.sym->name;
		case POINTER:
			if (!ischar(ty->type) && (p = findtype(ty)) != NULL)
				return *str ? stringf("%s %s", p->name, str) : p->name;
			str = stringf(isarray(ty->type) || isfunc(ty->type) ? "(*%s)" : "*%s", str);
			break;
		case FUNCTION:
			if ((p = findtype(ty)) != NULL)
				return *str ? stringf("%s %s", p->name, str) : p->name;
			if (ty->u.f.proto == 0)
				str = stringf("%s()", str);
			else if (ty->u.f.proto[0]) {
				int i;
				str = stringf("%s(%s", str, typestring(ty->u.f.proto[0], ""));
				for (i = 1; ty->u.f.proto[i]; i++)
					if (ty->u.f.proto[i] == voidtype)
						str = stringf("%s, ...", str);
					else
						str = stringf("%s, %s", str, typestring(ty->u.f.proto[i], ""));
				str = stringf("%s)", str);
			} else
				str = stringf("%s(void)", str);
			break;
		case ARRAY:
			if ((p = findtype(ty)) != NULL)
				return *str ? stringf("%s %s", p->name, str) : p->name;
			if (ty->type && ty->type->size > 0)
				str = stringf("%s[%d]", str, ty->size/ty->type->size);
			else
				str = stringf("%s[]", str);
			break;
		default: assert(0);
		}
	}
	assert(0); return 0;
}