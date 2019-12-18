#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* ty; } ;
struct TYPE_8__ {TYPE_1__* ptr; } ;
struct TYPE_7__ {int size; } ;
typedef  TYPE_3__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit (char*,...) ; 
 int /*<<< orphan*/  emit_expr (TYPE_3__*) ; 
 int /*<<< orphan*/  error (char*,char) ; 
 int /*<<< orphan*/  pop (char*) ; 
 int /*<<< orphan*/  push (char*) ; 

__attribute__((used)) static void emit_pointer_arith(char kind, Node *left, Node *right) {
    SAVE;
    emit_expr(left);
    push("rcx");
    push("rax");
    emit_expr(right);
    int size = left->ty->ptr->size;
    if (size > 1)
        emit("imul $%d, #rax", size);
    emit("mov #rax, #rcx");
    pop("rax");
    switch (kind) {
    case '+': emit("add #rcx, #rax"); break;
    case '-': emit("sub #rcx, #rax"); break;
    default: error("invalid operator '%d'", kind);
    }
    pop("rcx");
}