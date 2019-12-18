#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ is_ptr_type (TYPE_1__*) ; 
 int /*<<< orphan*/  qualify_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pointer_promo_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* type_char ; 
 int /*<<< orphan*/  type_ptr (int /*<<< orphan*/ ) ; 
 TYPE_1__* type_void ; 
 TYPE_1__* unqualify_type (int /*<<< orphan*/ ) ; 

bool compatible_pointer_arith(Type *left, Type *right, Expr *left_expr, Expr *right_expr) {
    if (is_ptr_type(left) && is_ptr_type(right)) {
        Type *left_base = unqualify_type(left->base);
        Type *right_base = unqualify_type(right->base);
        if (left_base == right_base) {
            return true;
        }
        if (left_base == type_void && right_base == type_char) {
            set_pointer_promo_type(left_expr, type_ptr(qualify_type(type_char, left->base)));
            return true;
        }
        if (left_base == type_char && right_base == type_void) {
            set_pointer_promo_type(right_expr, type_ptr(qualify_type(type_char, right->base)));
            return true;
        }
    }
    return false;
}