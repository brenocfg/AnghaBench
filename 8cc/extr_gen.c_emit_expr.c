#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {int kind; int /*<<< orphan*/  ty; int /*<<< orphan*/  struc; int /*<<< orphan*/  newlabel; struct TYPE_31__* operand; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
#define  AST_ADDR 153 
#define  AST_COMPOUND_STMT 152 
#define  AST_COMPUTED_GOTO 151 
#define  AST_CONV 150 
#define  AST_DECL 149 
#define  AST_DEREF 148 
#define  AST_FUNCALL 147 
#define  AST_FUNCDESG 146 
#define  AST_FUNCPTR_CALL 145 
#define  AST_GOTO 144 
#define  AST_GVAR 143 
#define  AST_IF 142 
#define  AST_LABEL 141 
#define  AST_LITERAL 140 
#define  AST_LVAR 139 
#define  AST_RETURN 138 
#define  AST_STRUCT_REF 137 
#define  AST_TERNARY 136 
#define  OP_CAST 135 
#define  OP_LABEL_ADDR 134 
#define  OP_LOGAND 133 
#define  OP_LOGOR 132 
#define  OP_POST_DEC 131 
#define  OP_POST_INC 130 
#define  OP_PRE_DEC 129 
#define  OP_PRE_INC 128 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit_addr (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_assign (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_binop (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_bitand (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_bitnot (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_bitor (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_cast (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_comma (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_compound_stmt (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_computed_goto (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_conv (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_decl (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_deref (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_func_call (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_goto (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_gvar (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label_addr (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_literal (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_load_struct_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_logand (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_lognot (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_logor (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_lvar (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_post_inc_dec (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  emit_pre_inc_dec (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  emit_return (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_ternary (TYPE_1__*) ; 
 int /*<<< orphan*/  maybe_emit_builtin (TYPE_1__*) ; 
 int /*<<< orphan*/  maybe_print_source_loc (TYPE_1__*) ; 

__attribute__((used)) static void emit_expr(Node *node) {
    SAVE;
    maybe_print_source_loc(node);
    switch (node->kind) {
    case AST_LITERAL: emit_literal(node); return;
    case AST_LVAR:    emit_lvar(node); return;
    case AST_GVAR:    emit_gvar(node); return;
    case AST_FUNCDESG: emit_addr(node); return;
    case AST_FUNCALL:
        if (maybe_emit_builtin(node))
            return;
        // fall through
    case AST_FUNCPTR_CALL:
        emit_func_call(node);
        return;
    case AST_DECL:    emit_decl(node); return;
    case AST_CONV:    emit_conv(node); return;
    case AST_ADDR:    emit_addr(node->operand); return;
    case AST_DEREF:   emit_deref(node); return;
    case AST_IF:
    case AST_TERNARY:
        emit_ternary(node);
        return;
    case AST_GOTO:    emit_goto(node); return;
    case AST_LABEL:
        if (node->newlabel)
            emit_label(node->newlabel);
        return;
    case AST_RETURN:  emit_return(node); return;
    case AST_COMPOUND_STMT: emit_compound_stmt(node); return;
    case AST_STRUCT_REF:
        emit_load_struct_ref(node->struc, node->ty, 0);
        return;
    case OP_PRE_INC:   emit_pre_inc_dec(node, "add"); return;
    case OP_PRE_DEC:   emit_pre_inc_dec(node, "sub"); return;
    case OP_POST_INC:  emit_post_inc_dec(node, "add"); return;
    case OP_POST_DEC:  emit_post_inc_dec(node, "sub"); return;
    case '!': emit_lognot(node); return;
    case '&': emit_bitand(node); return;
    case '|': emit_bitor(node); return;
    case '~': emit_bitnot(node); return;
    case OP_LOGAND: emit_logand(node); return;
    case OP_LOGOR:  emit_logor(node); return;
    case OP_CAST:   emit_cast(node); return;
    case ',': emit_comma(node); return;
    case '=': emit_assign(node); return;
    case OP_LABEL_ADDR: emit_label_addr(node); return;
    case AST_COMPUTED_GOTO: emit_computed_goto(node); return;
    default:
        emit_binop(node);
    }
}