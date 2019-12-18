#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {size_t num_params; int /*<<< orphan*/  ret; TYPE_3__* varargs_type; TYPE_3__** params; } ;
struct TYPE_21__ {TYPE_2__ func; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ Type ;
struct TYPE_19__ {size_t num_args; TYPE_11__** args; } ;
struct TYPE_23__ {TYPE_1__ call; } ;
struct TYPE_22__ {TYPE_3__* type; } ;
struct TYPE_18__ {int /*<<< orphan*/  pos; } ;
typedef  TYPE_4__ Operand ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  convert_operand (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_type_name (TYPE_3__*) ; 
 scalar_t__ is_array_type (TYPE_3__*) ; 
 TYPE_4__ operand_rvalue (int /*<<< orphan*/ ) ; 
 TYPE_4__ resolve_expected_expr_rvalue (TYPE_11__*,TYPE_3__*) ; 
 TYPE_3__* type_ptr (int /*<<< orphan*/ ) ; 

Operand resolve_expr_call_default(Operand func, Expr *expr) {
    size_t num_params = func.type->func.num_params;
    for (size_t i = 0; i < expr->call.num_args; i++) {
        Type *param_type = i < num_params ? func.type->func.params[i] : func.type->func.varargs_type;
        Operand arg = resolve_expected_expr_rvalue(expr->call.args[i], param_type);
        if (is_array_type(param_type)) {
            param_type = type_ptr(param_type->base);
        }
        if (!convert_operand(&arg, param_type)) {
            fatal_error(expr->call.args[i]->pos, "Invalid type in function call argument. Expected %s, got %s", get_type_name(param_type), get_type_name(arg.type));
        }
    }
    return operand_rvalue(func.type->func.ret);
}