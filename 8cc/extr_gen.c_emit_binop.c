#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ kind; } ;
struct TYPE_9__ {int kind; TYPE_3__* ty; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 scalar_t__ KIND_PTR ; 
#define  OP_EQ 130 
#define  OP_LE 129 
#define  OP_NE 128 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit_binop_float_arith (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_binop_int_arith (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_comp (char*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  emit_pointer_arith (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_flotype (TYPE_3__*) ; 
 scalar_t__ is_inttype (TYPE_3__*) ; 
 int /*<<< orphan*/  node2s (TYPE_1__*) ; 

__attribute__((used)) static void emit_binop(Node *node) {
    SAVE;
    if (node->ty->kind == KIND_PTR) {
        emit_pointer_arith(node->kind, node->left, node->right);
        return;
    }
    switch (node->kind) {
    case '<': emit_comp("setl", "setb", node); return;
    case OP_EQ: emit_comp("sete", "sete", node); return;
    case OP_LE: emit_comp("setle", "setna", node); return;
    case OP_NE: emit_comp("setne", "setne", node); return;
    }
    if (is_inttype(node->ty))
        emit_binop_int_arith(node);
    else if (is_flotype(node->ty))
        emit_binop_float_arith(node);
    else
        error("internal error: %s", node2s(node));
}