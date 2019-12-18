#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  args; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit (char*,...) ; 
 int /*<<< orphan*/  emit_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jmp (char*) ; 
 int /*<<< orphan*/  emit_label (char*) ; 
 char* make_label () ; 
 int /*<<< orphan*/  pop (char*) ; 
 int /*<<< orphan*/  push (char*) ; 
 int /*<<< orphan*/  vec_head (int /*<<< orphan*/ ) ; 
 int vec_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_builtin_return_address(Node *node) {
    push("r11");
    assert(vec_len(node->args) == 1);
    emit_expr(vec_head(node->args));
    char *loop = make_label();
    char *end = make_label();
    emit("mov #rbp, #r11");
    emit_label(loop);
    emit("test #rax, #rax");
    emit("jz %s", end);
    emit("mov (#r11), #r11");
    emit("sub $1, #rax");
    emit_jmp(loop);
    emit_label(end);
    emit("mov 8(#r11), #rax");
    pop("r11");
}