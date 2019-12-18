#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int kind; char* glabel; TYPE_1__* ty; int /*<<< orphan*/  lvarinit; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
#define  AST_GVAR 129 
#define  AST_LVAR 128 
 int /*<<< orphan*/  do_emit_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit (char*,...) ; 
 int /*<<< orphan*/  emit_label (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 char* make_label () ; 

__attribute__((used)) static void emit_data_addr(Node *operand, int depth) {
    switch (operand->kind) {
    case AST_LVAR: {
        char *label = make_label();
        emit(".data %d", depth + 1);
        emit_label(label);
        do_emit_data(operand->lvarinit, operand->ty->size, 0, depth + 1);
        emit(".data %d", depth);
        emit(".quad %s", label);
        return;
    }
    case AST_GVAR:
        emit(".quad %s", operand->glabel);
        return;
    default:
        error("internal error");
    }
}