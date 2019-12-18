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
 int /*<<< orphan*/  OP_EQ ; 
 int /*<<< orphan*/  OP_NE ; 
 TYPE_1__* binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conv (TYPE_1__*) ; 
 scalar_t__ next_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* read_relational_expr () ; 
 int /*<<< orphan*/  type_int ; 

__attribute__((used)) static Node *read_equality_expr() {
    Node *node = read_relational_expr();
    Node *r;
    if (next_token(OP_EQ)) {
        r = binop(OP_EQ, conv(node), conv(read_equality_expr()));
    } else if (next_token(OP_NE)) {
        r = binop(OP_NE, conv(node), conv(read_equality_expr()));
    } else {
        return node;
    }
    r->ty = type_int;
    return r;
}