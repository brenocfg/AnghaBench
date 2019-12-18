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
 int /*<<< orphan*/  REGAREA_SIZE ; 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit (char*,...) ; 
 int /*<<< orphan*/  emit_expr (int /*<<< orphan*/ ) ; 
 int numfp ; 
 int numgp ; 
 int /*<<< orphan*/  pop (char*) ; 
 int /*<<< orphan*/  push (char*) ; 
 int /*<<< orphan*/  vec_head (int /*<<< orphan*/ ) ; 
 int vec_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_builtin_va_start(Node *node) {
    SAVE;
    assert(vec_len(node->args) == 1);
    emit_expr(vec_head(node->args));
    push("rcx");
    emit("movl $%d, (#rax)", numgp * 8);
    emit("movl $%d, 4(#rax)", 48 + numfp * 16);
    emit("lea %d(#rbp), #rcx", -REGAREA_SIZE);
    emit("mov #rcx, 16(#rax)");
    pop("rcx");
}