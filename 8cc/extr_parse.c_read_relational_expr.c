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
struct TYPE_6__ {int /*<<< orphan*/  ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 char OP_GE ; 
 char OP_LE ; 
 TYPE_1__* binop (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conv (TYPE_1__*) ; 
 scalar_t__ next_token (char) ; 
 TYPE_1__* read_shift_expr () ; 
 int /*<<< orphan*/  type_int ; 

__attribute__((used)) static Node *read_relational_expr() {
    Node *node = read_shift_expr();
    for (;;) {
        if      (next_token('<'))   node = binop('<',   conv(node), conv(read_shift_expr()));
        else if (next_token('>'))   node = binop('<',   conv(read_shift_expr()), conv(node));
        else if (next_token(OP_LE)) node = binop(OP_LE, conv(node), conv(read_shift_expr()));
        else if (next_token(OP_GE)) node = binop(OP_LE, conv(read_shift_expr()), conv(node));
        else    return node;
        node->ty = type_int;
    }
}