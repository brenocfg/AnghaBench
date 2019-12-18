#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bitsize; int bitoff; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit (char*,...) ; 
 int /*<<< orphan*/  get_int_reg (TYPE_1__*,char) ; 
 int /*<<< orphan*/  pop (char*) ; 
 int /*<<< orphan*/  push (char*) ; 

__attribute__((used)) static void maybe_emit_bitshift_save(Type *ty, char *addr) {
    SAVE;
    if (ty->bitsize <= 0)
        return;
    push("rcx");
    push("rdi");
    emit("mov $0x%lx, #rdi", (1 << (long)ty->bitsize) - 1);
    emit("and #rdi, #rax");
    emit("shl $%d, #rax", ty->bitoff);
    emit("mov %s, #%s", addr, get_int_reg(ty, 'c'));
    emit("mov $0x%lx, #rdi", ~(((1 << (long)ty->bitsize) - 1) << ty->bitoff));
    emit("and #rdi, #rcx");
    emit("or #rcx, #rax");
    pop("rdi");
    pop("rcx");
}