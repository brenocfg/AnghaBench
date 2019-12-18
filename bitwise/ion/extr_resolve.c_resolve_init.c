#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Typespec ;
struct TYPE_26__ {scalar_t__ size; } ;
typedef  TYPE_1__ Type ;
struct TYPE_27__ {scalar_t__ kind; } ;
struct TYPE_25__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  TYPE_2__ Expr ;

/* Variables and functions */
 scalar_t__ EXPR_COMPOUND ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  complete_type (TYPE_1__*) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_type_name (TYPE_1__*) ; 
 TYPE_1__* incomplete_decay (TYPE_1__*) ; 
 scalar_t__ is_array_type (TYPE_1__*) ; 
 scalar_t__ is_ptr_type (TYPE_1__*) ; 
 TYPE_16__ resolve_expr (TYPE_2__*) ; 
 TYPE_1__* resolve_typed_init (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*) ; 
 TYPE_1__* resolve_typespec_strict (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_resolved_expected_type (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  set_resolved_type (TYPE_2__*,TYPE_1__*) ; 
 TYPE_1__* type_decay (TYPE_1__*) ; 
 TYPE_1__* unqualify_type (int /*<<< orphan*/ ) ; 

Type *resolve_init(SrcPos pos, Typespec *typespec, Expr *expr, bool was_const, bool is_undef) {
    Type *type = NULL;
    Type *inferred_type = NULL;
    Type *declared_type = NULL;
    if (is_undef) {
        if (typespec) {
            declared_type = type = resolve_typespec_strict(typespec, was_const);
        }
        if (!type) {
            fatal_error(pos, "Cannot use undef initializer without declared type");
        }
    } else if (typespec) {
        declared_type = type = resolve_typespec_strict(typespec, was_const);
        if (expr) {
            inferred_type = type = resolve_typed_init(pos, declared_type, expr);
            if (!inferred_type) {
                fatal_error(pos, "Invalid type in initialization. Expected %s", get_type_name(declared_type));
            }
        }
    } else {
        assert(expr);
        inferred_type = type = unqualify_type(resolve_expr(expr).type);
        if (is_array_type(type) && expr->kind != EXPR_COMPOUND) {
            type = type_decay(type);
            set_resolved_type(expr, type);
        }
        set_resolved_expected_type(expr, type);
    }
    complete_type(type);
    if (!expr || is_ptr_type(inferred_type)) {
        type = incomplete_decay(type);
    }
    if (type->size == 0) {
        fatal_error(pos, "Cannot declare variable of size 0");
    }
    return type;
}