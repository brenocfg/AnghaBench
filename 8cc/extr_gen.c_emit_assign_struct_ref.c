#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ offset; } ;
typedef  TYPE_2__ Type ;
struct TYPE_13__ {int kind; int /*<<< orphan*/  operand; TYPE_1__* ty; struct TYPE_13__* struc; int /*<<< orphan*/  glabel; scalar_t__ loff; } ;
struct TYPE_11__ {int /*<<< orphan*/  offset; } ;
typedef  TYPE_3__ Node ;

/* Variables and functions */
#define  AST_DEREF 131 
#define  AST_GVAR 130 
#define  AST_LVAR 129 
#define  AST_STRUCT_REF 128 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  do_emit_assign_deref (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_gsave (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_lsave (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_lvar_init (TYPE_3__*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node2s (TYPE_3__*) ; 
 int /*<<< orphan*/  push (char*) ; 

__attribute__((used)) static void emit_assign_struct_ref(Node *struc, Type *field, int off) {
    SAVE;
    switch (struc->kind) {
    case AST_LVAR:
        ensure_lvar_init(struc);
        emit_lsave(field, struc->loff + field->offset + off);
        break;
    case AST_GVAR:
        emit_gsave(struc->glabel, field, field->offset + off);
        break;
    case AST_STRUCT_REF:
        emit_assign_struct_ref(struc->struc, field, off + struc->ty->offset);
        break;
    case AST_DEREF:
        push("rax");
        emit_expr(struc->operand);
        do_emit_assign_deref(field, field->offset + off);
        break;
    default:
        error("internal error: %s", node2s(struc));
    }
}