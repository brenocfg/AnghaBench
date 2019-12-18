#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ offset; } ;
typedef  TYPE_2__ Type ;
struct TYPE_12__ {int kind; int /*<<< orphan*/  operand; TYPE_1__* ty; struct TYPE_12__* struc; int /*<<< orphan*/  glabel; scalar_t__ loff; } ;
struct TYPE_10__ {int /*<<< orphan*/  offset; } ;
typedef  TYPE_3__ Node ;

/* Variables and functions */
#define  AST_DEREF 131 
#define  AST_GVAR 130 
#define  AST_LVAR 129 
#define  AST_STRUCT_REF 128 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_gload (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_lload (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_lvar_init (TYPE_3__*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node2s (TYPE_3__*) ; 

__attribute__((used)) static void emit_load_struct_ref(Node *struc, Type *field, int off) {
    SAVE;
    switch (struc->kind) {
    case AST_LVAR:
        ensure_lvar_init(struc);
        emit_lload(field, "rbp", struc->loff + field->offset + off);
        break;
    case AST_GVAR:
        emit_gload(field, struc->glabel, field->offset + off);
        break;
    case AST_STRUCT_REF:
        emit_load_struct_ref(struc->struc, field, struc->ty->offset + off);
        break;
    case AST_DEREF:
        emit_expr(struc->operand);
        emit_lload(field, "rax", field->offset + off);
        break;
    default:
        error("internal error: %s", node2s(struc));
    }
}