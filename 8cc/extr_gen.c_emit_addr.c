#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int kind; int /*<<< orphan*/  fname; TYPE_1__* ty; struct TYPE_7__* struc; int /*<<< orphan*/  operand; int /*<<< orphan*/  glabel; int /*<<< orphan*/  loff; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
#define  AST_DEREF 132 
#define  AST_FUNCDESG 131 
#define  AST_GVAR 130 
#define  AST_LVAR 129 
#define  AST_STRUCT_REF 128 
 int /*<<< orphan*/  emit (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_lvar_init (TYPE_2__*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node2s (TYPE_2__*) ; 

__attribute__((used)) static void emit_addr(Node *node) {
    switch (node->kind) {
    case AST_LVAR:
        ensure_lvar_init(node);
        emit("lea %d(#rbp), #rax", node->loff);
        break;
    case AST_GVAR:
        emit("lea %s(#rip), #rax", node->glabel);
        break;
    case AST_DEREF:
        emit_expr(node->operand);
        break;
    case AST_STRUCT_REF:
        emit_addr(node->struc);
        emit("add $%d, #rax", node->ty->offset);
        break;
    case AST_FUNCDESG:
        emit("lea %s(#rip), #rax", node->fname);
        break;
    default:
        error("internal error: %s", node2s(node));
    }
}