#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ Operand ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cast_operand (TYPE_1__*,scalar_t__) ; 
 int is_integer_type (scalar_t__) ; 
 scalar_t__ is_signed_type (scalar_t__) ; 
 int /*<<< orphan*/  promote_operand (TYPE_1__*) ; 
 scalar_t__ type_double ; 
 scalar_t__ type_float ; 
 scalar_t__ type_rank (scalar_t__) ; 
 scalar_t__ type_sizeof (scalar_t__) ; 
 int /*<<< orphan*/ * unsigned_type (scalar_t__) ; 

void unify_arithmetic_operands(Operand *left, Operand *right) {
    if (left->type == type_double) {
        cast_operand(right, type_double);
    } else if (right->type == type_double) {
        cast_operand(left, type_double);
    } else if (left->type == type_float) {
        cast_operand(right, type_float);
    } else if (right->type == type_float) {
        cast_operand(left, type_float);
    } else {
        assert(is_integer_type(left->type));
        assert(is_integer_type(right->type));
        promote_operand(left);
        promote_operand(right);
        if (left->type != right->type) {
            if (is_signed_type(left->type) == is_signed_type(right->type)) {
                if (type_rank(left->type) <= type_rank(right->type)) {
                    cast_operand(left, right->type);
                } else {
                    cast_operand(right, left->type);
                }
            } else if (is_signed_type(left->type) && type_rank(right->type) >= type_rank(left->type)) {
                cast_operand(left, right->type);
            } else if (is_signed_type(right->type) && type_rank(left->type) >= type_rank(right->type)) {
                cast_operand(right, left->type);
            } else if (is_signed_type(left->type) && type_sizeof(left->type) > type_sizeof(right->type)) {
                cast_operand(right, left->type);            
            } else if (is_signed_type(right->type) && type_sizeof(right->type) > type_sizeof(left->type)) {
                cast_operand(left, right->type);
            } else { 
                Type *type = unsigned_type(is_signed_type(left->type) ? left->type : right->type);
                cast_operand(left, type);
                cast_operand(right, type);
            }
        }
    }
    assert(left->type == right->type);
}