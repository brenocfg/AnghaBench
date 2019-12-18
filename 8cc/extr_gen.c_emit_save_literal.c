#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  long uint64_t ;
typedef  long uint32_t ;
struct TYPE_7__ {int kind; } ;
typedef  TYPE_1__ Type ;
struct TYPE_8__ {long ival; float fval; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
#define  KIND_BOOL 137 
#define  KIND_CHAR 136 
#define  KIND_DOUBLE 135 
#define  KIND_FLOAT 134 
#define  KIND_INT 133 
#define  KIND_LDOUBLE 132 
#define  KIND_LLONG 131 
#define  KIND_LONG 130 
#define  KIND_PTR 129 
#define  KIND_SHORT 128 
 int /*<<< orphan*/  emit (char*,long,int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  node2s (TYPE_2__*) ; 
 char* ty2s (TYPE_1__*) ; 

__attribute__((used)) static void emit_save_literal(Node *node, Type *totype, int off) {
    switch (totype->kind) {
    case KIND_BOOL:  emit("movb $%d, %d(#rbp)", !!node->ival, off); break;
    case KIND_CHAR:  emit("movb $%d, %d(#rbp)", node->ival, off); break;
    case KIND_SHORT: emit("movw $%d, %d(#rbp)", node->ival, off); break;
    case KIND_INT:   emit("movl $%d, %d(#rbp)", node->ival, off); break;
    case KIND_LONG:
    case KIND_LLONG:
    case KIND_PTR: {
        emit("movl $%lu, %d(#rbp)", ((uint64_t)node->ival) & ((1L << 32) - 1), off);
        emit("movl $%lu, %d(#rbp)", ((uint64_t)node->ival) >> 32, off + 4);
        break;
    }
    case KIND_FLOAT: {
        float fval = node->fval;
        emit("movl $%u, %d(#rbp)", *(uint32_t *)&fval, off);
        break;
    }
    case KIND_DOUBLE:
    case KIND_LDOUBLE: {
        emit("movl $%lu, %d(#rbp)", *(uint64_t *)&node->fval & ((1L << 32) - 1), off);
        emit("movl $%lu, %d(#rbp)", *(uint64_t *)&node->fval >> 32, off + 4);
        break;
    }
    default:
        error("internal error: <%s> <%s> <%d>", node2s(node), ty2s(totype), off);
    }
}