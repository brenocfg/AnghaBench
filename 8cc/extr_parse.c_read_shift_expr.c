#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ usig; } ;
struct TYPE_8__ {TYPE_7__* ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int OP_SAL ; 
 int OP_SAR ; 
 int OP_SHR ; 
 TYPE_1__* ast_binop (TYPE_7__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conv (TYPE_1__*) ; 
 int /*<<< orphan*/  ensure_inttype (TYPE_1__*) ; 
 scalar_t__ next_token (int) ; 
 TYPE_1__* read_additive_expr () ; 

__attribute__((used)) static Node *read_shift_expr() {
    Node *node = read_additive_expr();
    for (;;) {
        int op;
        if (next_token(OP_SAL))
            op = OP_SAL;
        else if (next_token(OP_SAR))
            op = node->ty->usig ? OP_SHR : OP_SAR;
        else
            break;
        Node *right = read_additive_expr();
        ensure_inttype(node);
        ensure_inttype(right);
        node = ast_binop(node->ty, op, conv(node), conv(right));
    }
    return node;
}