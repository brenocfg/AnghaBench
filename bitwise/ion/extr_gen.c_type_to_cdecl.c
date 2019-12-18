#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t num_params; TYPE_2__* ret; int /*<<< orphan*/  has_varargs; TYPE_2__** params; } ;
struct TYPE_6__ {int kind; TYPE_1__ func; int /*<<< orphan*/  num_elems; struct TYPE_6__* base; } ;
typedef  TYPE_2__ Type ;

/* Variables and functions */
#define  TYPE_ARRAY 131 
#define  TYPE_CONST 130 
#define  TYPE_FUNC 129 
#define  TYPE_PTR 128 
 int /*<<< orphan*/  buf_printf (char*,char*,...) ; 
 int /*<<< orphan*/  cdecl_name (TYPE_2__*) ; 
 char* cdecl_paren (char const*,char const) ; 
 char* strf (char*,char const*,...) ; 

char *type_to_cdecl(Type *type, const char *str) {
    switch (type->kind) {
    case TYPE_PTR:
        return type_to_cdecl(type->base, cdecl_paren(strf("*%s", str), *str));
    case TYPE_CONST:
        return type_to_cdecl(type->base, strf("const %s", cdecl_paren(str, *str)));
    case TYPE_ARRAY:
        if (type->num_elems == 0) {
            return type_to_cdecl(type->base, cdecl_paren(strf("%s[]", str), *str));
        } else {
            return type_to_cdecl(type->base, cdecl_paren(strf("%s[%zu]", str, type->num_elems), *str));
        }
    case TYPE_FUNC: {
        char *result = NULL;
        buf_printf(result, "(*%s)(", str);
        if (type->func.num_params == 0) {
            buf_printf(result, "void");
        } else {
            for (size_t i = 0; i < type->func.num_params; i++) {
                buf_printf(result, "%s%s", i == 0 ? "" : ", ", type_to_cdecl(type->func.params[i], ""));
            }
        }
        if (type->func.has_varargs) {
            buf_printf(result, ", ...");
        }
        buf_printf(result, ")");
        return type_to_cdecl(type->func.ret, result);
    }
    default:
        return strf("%s%s%s", cdecl_name(type), *str ? " " : "", str);
    }
}