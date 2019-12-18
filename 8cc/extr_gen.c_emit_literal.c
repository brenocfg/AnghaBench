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
typedef  void* uint64_t ;
typedef  void* uint32_t ;
struct TYPE_5__ {float fval; void* slabel; TYPE_1__* ty; int /*<<< orphan*/  sval; void* flabel; void* ival; } ;
struct TYPE_4__ {int kind; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
#define  KIND_ARRAY 137 
#define  KIND_BOOL 136 
#define  KIND_CHAR 135 
#define  KIND_DOUBLE 134 
#define  KIND_FLOAT 133 
#define  KIND_INT 132 
#define  KIND_LDOUBLE 131 
#define  KIND_LLONG 130 
#define  KIND_LONG 129 
#define  KIND_SHORT 128 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit (char*,void*) ; 
 int /*<<< orphan*/  emit_label (void*) ; 
 int /*<<< orphan*/  emit_noindent (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 void* make_label () ; 
 void* quote_cstring_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_literal(Node *node) {
    SAVE;
    switch (node->ty->kind) {
    case KIND_BOOL:
    case KIND_CHAR:
    case KIND_SHORT:
        emit("mov $%u, #rax", node->ival);
        break;
    case KIND_INT:
        emit("mov $%u, #rax", node->ival);
        break;
    case KIND_LONG:
    case KIND_LLONG: {
        emit("mov $%lu, #rax", node->ival);
        break;
    }
    case KIND_FLOAT: {
        if (!node->flabel) {
            node->flabel = make_label();
            float fval = node->fval;
            emit_noindent(".data");
            emit_label(node->flabel);
            emit(".long %d", *(uint32_t *)&fval);
            emit_noindent(".text");
        }
        emit("movss %s(#rip), #xmm0", node->flabel);
        break;
    }
    case KIND_DOUBLE:
    case KIND_LDOUBLE: {
        if (!node->flabel) {
            node->flabel = make_label();
            emit_noindent(".data");
            emit_label(node->flabel);
            emit(".quad %lu", *(uint64_t *)&node->fval);
            emit_noindent(".text");
        }
        emit("movsd %s(#rip), #xmm0", node->flabel);
        break;
    }
    case KIND_ARRAY: {
        if (!node->slabel) {
            node->slabel = make_label();
            emit_noindent(".data");
            emit_label(node->slabel);
            emit(".string \"%s\"", quote_cstring_len(node->sval, node->ty->size - 1));
            emit_noindent(".text");
        }
        emit("lea %s(#rip), #rax", node->slabel);
        break;
    }
    default:
        error("internal error");
    }
}