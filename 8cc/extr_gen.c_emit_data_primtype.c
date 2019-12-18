#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {int kind; TYPE_9__* ptr; } ;
typedef  TYPE_1__ Type ;
struct TYPE_12__ {int const kind; int size; } ;
struct TYPE_11__ {float fval; int /*<<< orphan*/  glabel; int /*<<< orphan*/  kind; struct TYPE_11__* operand; TYPE_1__* ty; int /*<<< orphan*/  sval; int /*<<< orphan*/  newlabel; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  AST_ADDR ; 
 int /*<<< orphan*/  AST_CONV ; 
 int /*<<< orphan*/  AST_GVAR ; 
 int KIND_ARRAY ; 
#define  KIND_BOOL 136 
#define  KIND_CHAR 135 
#define  KIND_DOUBLE 134 
#define  KIND_FLOAT 133 
#define  KIND_INT 132 
#define  KIND_LLONG 131 
#define  KIND_LONG 130 
#define  KIND_PTR 129 
#define  KIND_SHORT 128 
 int /*<<< orphan*/  OP_LABEL_ADDR ; 
 int /*<<< orphan*/  assert (TYPE_9__*) ; 
 int /*<<< orphan*/  emit (char*,int,...) ; 
 int /*<<< orphan*/  emit_data_charptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  error (char*,char*,...) ; 
 int eval_intexpr (TYPE_2__*,TYPE_2__**) ; 
 char* node2s (TYPE_2__*) ; 
 int /*<<< orphan*/  ty2s (TYPE_1__*) ; 

__attribute__((used)) static void emit_data_primtype(Type *ty, Node *val, int depth) {
    switch (ty->kind) {
    case KIND_FLOAT: {
        float f = val->fval;
        emit(".long %d", *(uint32_t *)&f);
        break;
    }
    case KIND_DOUBLE:
        emit(".quad %ld", *(uint64_t *)&val->fval);
        break;
    case KIND_BOOL:
        emit(".byte %d", !!eval_intexpr(val, NULL));
        break;
    case KIND_CHAR:
        emit(".byte %d", eval_intexpr(val, NULL));
        break;
    case KIND_SHORT:
        emit(".short %d", eval_intexpr(val, NULL));
        break;
    case KIND_INT:
        emit(".long %d", eval_intexpr(val, NULL));
        break;
    case KIND_LONG:
    case KIND_LLONG:
    case KIND_PTR:
        if (val->kind == OP_LABEL_ADDR) {
            emit(".quad %s", val->newlabel);
            break;
        }
        bool is_char_ptr = (val->operand->ty->kind == KIND_ARRAY && val->operand->ty->ptr->kind == KIND_CHAR);
        if (is_char_ptr) {
            emit_data_charptr(val->operand->sval, depth);
        } else if (val->kind == AST_GVAR) {
            emit(".quad %s", val->glabel);
        } else {
            Node *base = NULL;
            int v = eval_intexpr(val, &base);
            if (base == NULL) {
                emit(".quad %u", v);
                break;
            }
            Type *ty = base->ty;
            if (base->kind == AST_CONV || base->kind == AST_ADDR)
                base = base->operand;
            if (base->kind != AST_GVAR)
                error("global variable expected, but got %s", node2s(base));
            assert(ty->ptr);
            emit(".quad %s+%u", base->glabel, v * ty->ptr->size);
        }
        break;
    default:
        error("don't know how to handle\n  <%s>\n  <%s>", ty2s(ty), node2s(val));
    }
}