#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ kind; int /*<<< orphan*/  body; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 scalar_t__ AST_DECL ; 
 scalar_t__ AST_FUNC ; 
 int /*<<< orphan*/  emit_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_func_prologue (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_global_var (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_ret () ; 
 int /*<<< orphan*/  error (char*) ; 
 int stackpos ; 

void emit_toplevel(Node *v) {
    stackpos = 8;
    if (v->kind == AST_FUNC) {
        emit_func_prologue(v);
        emit_expr(v->body);
        emit_ret();
    } else if (v->kind == AST_DECL) {
        emit_global_var(v);
    } else {
        error("internal error");
    }
}