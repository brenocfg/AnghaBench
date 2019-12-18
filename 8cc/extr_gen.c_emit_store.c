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
struct TYPE_5__ {int kind; int /*<<< orphan*/  ty; int /*<<< orphan*/  glabel; int /*<<< orphan*/  loff; int /*<<< orphan*/  struc; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
#define  AST_DEREF 131 
#define  AST_GVAR 130 
#define  AST_LVAR 129 
#define  AST_STRUCT_REF 128 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit_assign_deref (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_assign_struct_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_gsave (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_lsave (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_lvar_init (TYPE_1__*) ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static void emit_store(Node *var) {
    SAVE;
    switch (var->kind) {
    case AST_DEREF: emit_assign_deref(var); break;
    case AST_STRUCT_REF: emit_assign_struct_ref(var->struc, var->ty, 0); break;
    case AST_LVAR:
        ensure_lvar_init(var);
        emit_lsave(var->ty, var->loff);
        break;
    case AST_GVAR: emit_gsave(var->glabel, var->ty, 0); break;
    default: error("internal error");
    }
}