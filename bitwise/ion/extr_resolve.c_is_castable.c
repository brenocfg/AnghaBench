#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_4__ {int /*<<< orphan*/ * type; } ;
typedef  TYPE_1__ Operand ;

/* Variables and functions */
 scalar_t__ is_convertible (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_integer_type (int /*<<< orphan*/ *) ; 
 int is_ptr_like_type (int /*<<< orphan*/ *) ; 

bool is_castable(Operand *operand, Type *dest) {
    Type *src = operand->type;
    if (is_convertible(operand, dest)) {
        return true;
    } else if (is_integer_type(dest)) {
        return is_ptr_like_type(src);
    } else if (is_integer_type(src)) {
        return is_ptr_like_type(dest);
    } else if (is_ptr_like_type(dest) && is_ptr_like_type(src)) {
        return true;
    } else {
        return false;
    }
}