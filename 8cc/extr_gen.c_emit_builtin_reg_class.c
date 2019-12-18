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
struct TYPE_8__ {scalar_t__ kind; } ;
typedef  TYPE_2__ Type ;
struct TYPE_9__ {TYPE_1__* ty; int /*<<< orphan*/  args; } ;
struct TYPE_7__ {scalar_t__ kind; TYPE_2__* ptr; } ;
typedef  TYPE_3__ Node ;

/* Variables and functions */
 scalar_t__ KIND_PTR ; 
 scalar_t__ KIND_STRUCT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit (char*) ; 
 scalar_t__ is_flotype (TYPE_2__*) ; 
 TYPE_3__* vec_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_builtin_reg_class(Node *node) {
    Node *arg = vec_get(node->args, 0);
    assert(arg->ty->kind == KIND_PTR);
    Type *ty = arg->ty->ptr;
    if (ty->kind == KIND_STRUCT)
        emit("mov $2, #eax");
    else if (is_flotype(ty))
        emit("mov $1, #eax");
    else
        emit("mov $0, #eax");
}