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
typedef  int /*<<< orphan*/  TokenKind ;
struct TYPE_6__ {int /*<<< orphan*/  val; int /*<<< orphan*/  type; scalar_t__ is_const; } ;
typedef  TYPE_1__ Operand ;

/* Variables and functions */
 int /*<<< orphan*/  eval_unary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ operand_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  promote_operand (TYPE_1__*) ; 

Operand resolve_unary_op(TokenKind op, Operand operand) {
    promote_operand(&operand);
    if (operand.is_const) {
        return operand_const(operand.type, eval_unary_op(op, operand.type, operand.val));
    } else {
        return operand;
    }
}