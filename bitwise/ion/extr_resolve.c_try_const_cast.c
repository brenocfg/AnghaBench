#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_3__ {int /*<<< orphan*/ * type; int /*<<< orphan*/  is_lvalue; } ;
typedef  TYPE_1__ Operand ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  set_type_conv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * unqualify_ptr_type (int /*<<< orphan*/ *) ; 

void try_const_cast(Operand *operand, Expr *expr) {
    Type *unqual = unqualify_ptr_type(operand->type);
    if (!operand->is_lvalue && unqual != operand->type) {
        set_type_conv(expr, unqual);
        operand->type = unqual;
    }
}