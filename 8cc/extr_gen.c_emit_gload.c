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
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit (char*,char*,...) ; 
 char* get_load_inst (TYPE_1__*) ; 
 int /*<<< orphan*/  maybe_emit_bitshift_load (TYPE_1__*) ; 

__attribute__((used)) static void emit_gload(Type *ty, char *label, int off) {
    SAVE;
    if (ty->kind == KIND_ARRAY) {
        if (off)
            emit("lea %s+%d(#rip), #rax", label, off);
        else
            emit("lea %s(#rip), #rax", label);
        return;
    }
    char *inst = get_load_inst(ty);
    emit("%s %s+%d(#rip), #rax", inst, label, off);
    maybe_emit_bitshift_load(ty);
}