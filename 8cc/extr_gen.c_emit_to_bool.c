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
struct TYPE_4__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 scalar_t__ KIND_FLOAT ; 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit (char*,...) ; 
 scalar_t__ is_flotype (TYPE_1__*) ; 
 int /*<<< orphan*/  pop_xmm (int) ; 
 int /*<<< orphan*/  push_xmm (int) ; 

__attribute__((used)) static void emit_to_bool(Type *ty) {
    SAVE;
    if (is_flotype(ty)) {
        push_xmm(1);
        emit("xorpd #xmm1, #xmm1");
        emit("%s #xmm1, #xmm0", (ty->kind == KIND_FLOAT) ? "ucomiss" : "ucomisd");
        emit("setne #al");
        pop_xmm(1);
    } else {
        emit("cmp $0, #rax");
        emit("setne #al");
    }
    emit("movzb #al, #eax");
}