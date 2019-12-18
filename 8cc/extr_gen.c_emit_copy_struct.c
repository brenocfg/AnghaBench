#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ty; } ;
struct TYPE_6__ {int size; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  emit (char*,...) ; 
 int /*<<< orphan*/  emit_addr (TYPE_2__*) ; 
 int /*<<< orphan*/  pop (char*) ; 
 int /*<<< orphan*/  push (char*) ; 

__attribute__((used)) static void emit_copy_struct(Node *left, Node *right) {
    push("rcx");
    push("r11");
    emit_addr(right);
    emit("mov #rax, #rcx");
    emit_addr(left);
    int i = 0;
    for (; i < left->ty->size; i += 8) {
        emit("movq %d(#rcx), #r11", i);
        emit("movq #r11, %d(#rax)", i);
    }
    for (; i < left->ty->size; i += 4) {
        emit("movl %d(#rcx), #r11", i);
        emit("movl #r11, %d(#rax)", i);
    }
    for (; i < left->ty->size; i++) {
        emit("movb %d(#rcx), #r11", i);
        emit("movb #r11, %d(#rax)", i);
    }
    pop("r11");
    pop("rcx");
}