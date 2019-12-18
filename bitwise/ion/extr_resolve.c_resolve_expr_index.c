#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;

/* Type definitions */
struct TYPE_24__ {long long u; } ;
struct TYPE_19__ {int /*<<< orphan*/  index; int /*<<< orphan*/  expr; } ;
struct TYPE_23__ {scalar_t__ kind; int /*<<< orphan*/  pos; TYPE_1__ index; } ;
struct TYPE_22__ {TYPE_14__* type; TYPE_6__ val; int /*<<< orphan*/  is_const; } ;
struct TYPE_21__ {TYPE_2__* fields; scalar_t__ num_fields; } ;
struct TYPE_20__ {TYPE_14__* type; } ;
struct TYPE_18__ {int /*<<< orphan*/  base; TYPE_3__ aggregate; } ;
typedef  TYPE_4__ Operand ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 scalar_t__ EXPR_INDEX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  convert_operand (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_aggregate_type (TYPE_14__*) ; 
 int /*<<< orphan*/  is_integer_type (TYPE_14__*) ; 
 int /*<<< orphan*/  is_ptr_type (TYPE_14__*) ; 
 TYPE_4__ operand_decay (TYPE_4__) ; 
 TYPE_4__ operand_lvalue (int /*<<< orphan*/ ) ; 
 TYPE_4__ resolve_expr (int /*<<< orphan*/ ) ; 
 TYPE_4__ resolve_expr_rvalue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_resolved_val (int /*<<< orphan*/ ,TYPE_6__) ; 
 int /*<<< orphan*/  type_llong ; 

Operand resolve_expr_index(Expr *expr) {
    assert(expr->kind == EXPR_INDEX);
    Operand index = resolve_expr_rvalue(expr->index.index);
    if (!is_integer_type(index.type)) {
        fatal_error(expr->pos, "Index must have integer type");
    }
    Operand operand = resolve_expr(expr->index.expr);
    if (is_aggregate_type(operand.type)) {
        if (!index.is_const) {
            fatal_error(expr->pos, "Aggregate field index must be an integer constant");
        }
        convert_operand(&index, type_llong);
        set_resolved_val(expr->index.index, index.val);
        long long i = index.val.u;
        if (!(0 <= i && i < (long long)operand.type->aggregate.num_fields)) {
            fatal_error(expr->pos, "Aggregate field index out of range");
        }
        operand.type = operand.type->aggregate.fields[i].type;
        return operand;
    }
    operand = operand_decay(operand);
    if (!is_ptr_type(operand.type)) {
        fatal_error(expr->pos, "Can only index aggregates, arrays and pointers");
    }
    return operand_lvalue(operand.type->base);
}