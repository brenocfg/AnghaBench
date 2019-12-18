#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ty; } ;
struct TYPE_6__ {int kind; TYPE_3__* left; TYPE_1__* ty; TYPE_3__* right; } ;
struct TYPE_5__ {scalar_t__ usig; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
#define  OP_SAL 130 
#define  OP_SAR 129 
#define  OP_SHR 128 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit (char*,...) ; 
 int /*<<< orphan*/  emit_expr (TYPE_3__*) ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  get_int_reg (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pop (char*) ; 
 int /*<<< orphan*/  push (char*) ; 

__attribute__((used)) static void emit_binop_int_arith(Node *node) {
    SAVE;
    char *op = NULL;
    switch (node->kind) {
    case '+': op = "add"; break;
    case '-': op = "sub"; break;
    case '*': op = "imul"; break;
    case '^': op = "xor"; break;
    case OP_SAL: op = "sal"; break;
    case OP_SAR: op = "sar"; break;
    case OP_SHR: op = "shr"; break;
    case '/': case '%': break;
    default: error("invalid operator '%d'", node->kind);
    }
    emit_expr(node->left);
    push("rax");
    emit_expr(node->right);
    emit("mov #rax, #rcx");
    pop("rax");
    if (node->kind == '/' || node->kind == '%') {
        if (node->ty->usig) {
          emit("xor #edx, #edx");
          emit("div #rcx");
        } else {
          emit("cqto");
          emit("idiv #rcx");
        }
        if (node->kind == '%')
            emit("mov #edx, #eax");
    } else if (node->kind == OP_SAL || node->kind == OP_SAR || node->kind == OP_SHR) {
        emit("%s #cl, #%s", op, get_int_reg(node->left->ty, 'a'));
    } else {
        emit("%s #rcx, #rax", op);
    }
}