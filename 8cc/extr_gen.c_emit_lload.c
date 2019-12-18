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
struct TYPE_5__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 scalar_t__ KIND_ARRAY ; 
 scalar_t__ KIND_DOUBLE ; 
 scalar_t__ KIND_FLOAT ; 
 scalar_t__ KIND_LDOUBLE ; 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit (char*,...) ; 
 char* get_load_inst (TYPE_1__*) ; 
 int /*<<< orphan*/  maybe_emit_bitshift_load (TYPE_1__*) ; 

__attribute__((used)) static void emit_lload(Type *ty, char *base, int off) {
    SAVE;
    if (ty->kind == KIND_ARRAY) {
        emit("lea %d(#%s), #rax", off, base);
    } else if (ty->kind == KIND_FLOAT) {
        emit("movss %d(#%s), #xmm0", off, base);
    } else if (ty->kind == KIND_DOUBLE || ty->kind == KIND_LDOUBLE) {
        emit("movsd %d(#%s), #xmm0", off, base);
    } else {
        char *inst = get_load_inst(ty);
        emit("%s %d(#%s), #rax", inst, off, base);
        maybe_emit_bitshift_load(ty);
    }
}