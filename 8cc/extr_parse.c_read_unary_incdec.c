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
struct TYPE_9__ {int /*<<< orphan*/  ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 TYPE_1__* ast_uop (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* conv (TYPE_1__*) ; 
 int /*<<< orphan*/  ensure_lvalue (TYPE_1__*) ; 
 TYPE_1__* read_unary_expr () ; 

__attribute__((used)) static Node *read_unary_incdec(int op) {
    Node *operand = read_unary_expr();
    operand = conv(operand);
    ensure_lvalue(operand);
    return ast_uop(op, operand->ty, operand);
}