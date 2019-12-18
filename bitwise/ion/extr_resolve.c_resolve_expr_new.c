#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_18__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_11__ ;

/* Type definitions */
struct TYPE_30__ {struct TYPE_30__* base; } ;
typedef  TYPE_2__ Type ;
struct TYPE_29__ {TYPE_11__* len; TYPE_18__* arg; TYPE_16__* alloc; } ;
struct TYPE_32__ {TYPE_1__ new_expr; int /*<<< orphan*/  pos; } ;
struct TYPE_31__ {TYPE_2__* type; int /*<<< orphan*/  is_lvalue; } ;
struct TYPE_28__ {int /*<<< orphan*/  pos; } ;
struct TYPE_27__ {int /*<<< orphan*/  pos; } ;
struct TYPE_26__ {int /*<<< orphan*/  pos; } ;
typedef  TYPE_3__ Operand ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  complete_type (TYPE_2__*) ; 
 int /*<<< orphan*/  convert_operand (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_integer_type (TYPE_2__*) ; 
 scalar_t__ is_ptr_type (TYPE_2__*) ; 
 TYPE_3__ operand_rvalue (TYPE_2__*) ; 
 TYPE_3__ resolve_expected_expr (TYPE_18__*,TYPE_2__*) ; 
 TYPE_3__ resolve_expr (TYPE_16__*) ; 
 TYPE_3__ resolve_expr_rvalue (TYPE_11__*) ; 
 int /*<<< orphan*/  type_allocator_ptr ; 
 TYPE_2__* type_decay (TYPE_2__*) ; 
 TYPE_2__* type_ptr (TYPE_2__*) ; 
 scalar_t__ type_sizeof (TYPE_2__*) ; 

Operand resolve_expr_new(Expr *expr, Type *expected_type) {
    if (expr->new_expr.alloc) {
        Operand alloc = resolve_expr(expr->new_expr.alloc);
        if (!convert_operand(&alloc, type_allocator_ptr)) {
            fatal_error(expr->new_expr.alloc->pos, "Allocator of new must have type Allocator* or be pointer to struct with leading field of type Allocator");
        }
    }
    if (expr->new_expr.len) {
        Operand len = resolve_expr_rvalue(expr->new_expr.len);
        if (!is_integer_type(len.type)) {
            fatal_error(expr->new_expr.len->pos, "Length argument of new must have integer type");
        }
    }
    Type *expected_base = NULL;
    if (is_ptr_type(expected_type)) {
        expected_base = expected_type->base;
    }
    if (!expr->new_expr.arg) {
        expected_type = type_decay(expected_type);
        if (!is_ptr_type(expected_type)) {
            fatal_error(expr->pos, "New with void argument must have expected pointer type");
        }
        return operand_rvalue(expected_type);
    } else {
        Operand arg = resolve_expected_expr(expr->new_expr.arg, expr->new_expr.len ? expected_type : expected_base);
        if (expr->new_expr.len) {
            if (!is_ptr_type(arg.type)) {
                fatal_error(expr->new_expr.arg->pos, "Argument to new[] must have pointer type");
            }
        } else {
            if (!arg.is_lvalue) {
                fatal_error(expr->new_expr.arg->pos, "Argument to new must be lvalue");
            }
        }
        complete_type(arg.type);
        if (type_sizeof(arg.type) == 0) {
            fatal_error(expr->new_expr.arg->pos, "Type of argument to new has zero size");
        }
        return operand_rvalue(expr->new_expr.len ? arg.type : type_ptr(arg.type));
    }
}