#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TokenKind ;
typedef  int /*<<< orphan*/  Operand ;

/* Variables and functions */
 int /*<<< orphan*/  resolve_binary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unify_arithmetic_operands (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

Operand resolve_binary_arithmetic_op(TokenKind op, Operand left, Operand right) {
    unify_arithmetic_operands(&left, &right);
    return resolve_binary_op(op, left, right);
}