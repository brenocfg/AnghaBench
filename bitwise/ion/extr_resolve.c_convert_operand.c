#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_5__ {int is_lvalue; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Operand ;

/* Variables and functions */
 int /*<<< orphan*/  cast_operand (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_convertible (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unqualify_type (int /*<<< orphan*/ ) ; 

bool convert_operand(Operand *operand, Type *type) {
    if (is_convertible(operand, type)) {
        cast_operand(operand, type);
        operand->type = unqualify_type(operand->type);
        operand->is_lvalue = false;
        return true;
    }
    return false;
}