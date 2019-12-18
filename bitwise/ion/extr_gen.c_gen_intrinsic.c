#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int num_fields; TYPE_1__* fields; } ;
struct TYPE_20__ {struct TYPE_20__* base; TYPE_2__ aggregate; } ;
typedef  TYPE_4__ Type ;
struct TYPE_19__ {int num_args; TYPE_6__** args; } ;
struct TYPE_22__ {int /*<<< orphan*/  pos; TYPE_3__ call; } ;
struct TYPE_21__ {scalar_t__ name; } ;
struct TYPE_17__ {TYPE_4__* type; } ;
typedef  TYPE_5__ Sym ;
typedef  TYPE_6__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  gen_expr (TYPE_6__*) ; 
 int /*<<< orphan*/  genf (char*,...) ; 
 TYPE_4__* get_resolved_type (TYPE_6__*) ; 
 scalar_t__ is_aggregate_type (TYPE_4__*) ; 
 int is_ptr_type (TYPE_4__*) ; 
 scalar_t__ str_intern (char*) ; 
 int /*<<< orphan*/  type_to_cdecl (TYPE_4__*,char*) ; 
 TYPE_4__* unqualify_type (TYPE_4__*) ; 

void gen_intrinsic(Sym *sym, Expr *expr) {
    Type *type = get_resolved_type(expr->call.args[0]);
    Type *base = is_ptr_type(type) ? unqualify_type(type->base) : 0;
    Type *key = base && is_aggregate_type(base) && base->aggregate.num_fields == 2 ? base->aggregate.fields[0].type : 0;
    Type *val = base && is_aggregate_type(base) && base->aggregate.num_fields == 2 ? base->aggregate.fields[1].type : 0;
    if (sym->name == str_intern("va_copy") || sym->name == str_intern("va_start") || sym->name == str_intern("va_end")) {
        genf("%s(", sym->name);
        for (int i = 0; i < expr->call.num_args; i++) {
            if (i != 0) {
                genf(", ");
            }
            gen_expr(expr->call.args[i]);
        }
        genf(")");
    } else if (sym->name == str_intern("va_arg")) {
        assert(expr->call.num_args == 2);
        gen_expr(expr->call.args[1]);
        genf(" = va_arg(");
        gen_expr(expr->call.args[0]);
        Type *type = get_resolved_type(expr->call.args[1]);
        genf(", %s)", type_to_cdecl(type, ""));
    } else if (sym->name == str_intern("apush") || sym->name == str_intern("aputv") || sym->name == str_intern("adelv") ||
        sym->name == str_intern("agetvi") || sym->name == str_intern("agetvp") || sym->name == str_intern("agetv") ||
        sym->name == str_intern("asetcap") || sym->name == str_intern("afit") || sym->name == str_intern("acat") ||
        sym->name == str_intern("adeli") || sym->name == str_intern("aindexv") || sym->name == str_intern("asetlen")) {
        // (t, a, v)
        genf("%s(%s, (", sym->name, type_to_cdecl(base, ""));
        gen_expr(expr->call.args[0]);
        genf("), (");
        gen_expr(expr->call.args[1]);
        genf("))");
    } else if (sym->name == str_intern("adefault")) {
        // (t, tv, a, v)
        genf("%s(%s, %s, (", sym->name, type_to_cdecl(base, ""), type_to_cdecl(val, ""));
        gen_expr(expr->call.args[0]);
        genf("), (");
        gen_expr(expr->call.args[1]);
        genf("))");
    } else if (sym->name == str_intern("afill")) {
        // (t, a, v, n)
        genf("%s(%s, (", sym->name, type_to_cdecl(base, ""));
        gen_expr(expr->call.args[0]);
        genf("), (");
        gen_expr(expr->call.args[1]);
        genf("), (");
        gen_expr(expr->call.args[2]);
        genf("))");
    } else if (sym->name == str_intern("acatn") || sym->name == str_intern("adeln")) {
        genf("%s(%s, (", sym->name, type_to_cdecl(base, ""));
        gen_expr(expr->call.args[0]);
        genf("), (");
        gen_expr(expr->call.args[1]);
        genf("), (");
        gen_expr(expr->call.args[2]);
        genf("))");
    } else if (sym->name == str_intern("aindex") || sym->name == str_intern("ageti") || sym->name == str_intern("adel")) {
        genf("%s(%s, %s, (", sym->name, type_to_cdecl(base, ""), type_to_cdecl(key, ""));
        gen_expr(expr->call.args[0]);
        genf("), (");
        gen_expr(expr->call.args[1]);
        genf("))");
    } else if (sym->name == str_intern("agetp") || sym->name == str_intern("aget")) {
        genf("%s(%s, %s, %s, (", sym->name, type_to_cdecl(base, ""), type_to_cdecl(key, ""), type_to_cdecl(val, ""));
        gen_expr(expr->call.args[0]);
        genf("), (");
        gen_expr(expr->call.args[1]);
        genf("))");
    } else if (sym->name == str_intern("aput")) {
        genf("%s(%s, %s, (", sym->name, type_to_cdecl(base, ""), type_to_cdecl(key, ""));
        gen_expr(expr->call.args[0]);
        genf("), (");
        gen_expr(expr->call.args[1]);
        genf("), (");
        gen_expr(expr->call.args[2]);
        genf("))");
    } else if (sym->name == str_intern("ahdrsize") || sym->name == str_intern("ahdralign") || sym->name == str_intern("ahdr") ||
        sym->name == str_intern("alen") || sym->name == str_intern("acap") || sym->name == str_intern("afree") ||
        sym->name == str_intern("aclear") || sym->name == str_intern("apop")) {
        genf("%s(%s, (", sym->name, type_to_cdecl(base, ""));
        gen_expr(expr->call.args[0]);
        genf("))");
    } else if (sym->name == str_intern("anew")) {
        Type *result_type = get_resolved_type(expr);
        assert(is_ptr_type(result_type));
        genf("%s(%s, ", sym->name, type_to_cdecl(result_type->base, ""));
        gen_expr(expr->call.args[0]);
        genf(")");
    } else {
        fatal_error(expr->pos, "Call to unimplemented intrinsic %s", sym->name);
    }
}