#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t num_args; TYPE_2__* ret; int /*<<< orphan*/  has_varargs; TYPE_2__** args; } ;
struct TYPE_9__ {int kind; TYPE_1__ func; int /*<<< orphan*/  num_elems; struct TYPE_9__* base; } ;
typedef  TYPE_2__ Typespec ;
struct TYPE_10__ {char const* typeid; } ;
typedef  TYPE_3__ Type ;

/* Variables and functions */
#define  TYPESPEC_ARRAY 133 
#define  TYPESPEC_CONST 132 
#define  TYPESPEC_FUNC 131 
#define  TYPESPEC_NAME 130 
#define  TYPESPEC_PTR 129 
#define  TYPESPEC_TUPLE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_printf (char*,char*,...) ; 
 char* cdecl_paren (char*,char const) ; 
 char const* gen_expr_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_gen_name (TYPE_2__*) ; 
 TYPE_3__* get_resolved_type (TYPE_2__*) ; 
 char* strf (char*,char const*,...) ; 

char *typespec_to_cdecl(Typespec *typespec, const char *str) {
    if (!typespec) {
        return strf("void%s%s", *str ? " " : "", str);
    }
    switch (typespec->kind) {
    case TYPESPEC_NAME:
        return strf("%s%s%s", get_gen_name(typespec), *str ? " " : "", str);
    case TYPESPEC_PTR:
        return typespec_to_cdecl(typespec->base, cdecl_paren(strf("*%s", str), *str));
    case TYPESPEC_CONST:
        return typespec_to_cdecl(typespec->base, str);
        // return typespec_to_cdecl(typespec->base, strf("const %s", cdecl_paren(str, *str)));
    case TYPESPEC_ARRAY:
        if (typespec->num_elems == 0) {
            return typespec_to_cdecl(typespec->base, cdecl_paren(strf("%s[]", str), *str));
        } else {
            return typespec_to_cdecl(typespec->base, cdecl_paren(strf("%s[%s]", str, gen_expr_str(typespec->num_elems)), *str));
        }
    case TYPESPEC_FUNC: {
        char *result = NULL;
        buf_printf(result, "(*%s)(", str);
        if (typespec->func.num_args == 0) {
            buf_printf(result, "void");
        } else {
            for (size_t i = 0; i < typespec->func.num_args; i++) {
                buf_printf(result, "%s%s", i == 0 ? "" : ", ", typespec_to_cdecl(typespec->func.args[i], ""));
            }
        }
        if (typespec->func.has_varargs) {
            buf_printf(result, ", ...");
        }
        buf_printf(result, ")");
        return typespec_to_cdecl(typespec->func.ret, result);
    }
    case TYPESPEC_TUPLE: {
        Type *type = get_resolved_type(typespec);
        return strf("tuple%d %s", type->typeid, str);
    }
    default:
        assert(0);
        return NULL;
    }
}