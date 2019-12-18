#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_7__ {scalar_t__ kind; int /*<<< orphan*/  size; } ;
struct TYPE_6__ {TYPE_3__* ty; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 scalar_t__ KIND_STRUCT ; 
 int /*<<< orphan*/  SAVE ; 
 int /*<<< orphan*/  emit_addr (TYPE_1__*) ; 
 int /*<<< orphan*/  emit_expr (TYPE_1__*) ; 
 scalar_t__ is_flotype (TYPE_3__*) ; 
 int /*<<< orphan*/  push (char*) ; 
 scalar_t__ push_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_xmm (int /*<<< orphan*/ ) ; 
 TYPE_1__* vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int emit_args(Vector *vals) {
    SAVE;
    int r = 0;
    for (int i = 0; i < vec_len(vals); i++) {
        Node *v = vec_get(vals, i);
        if (v->ty->kind == KIND_STRUCT) {
            emit_addr(v);
            r += push_struct(v->ty->size);
        } else if (is_flotype(v->ty)) {
            emit_expr(v);
            push_xmm(0);
            r += 8;
        } else {
            emit_expr(v);
            push("rax");
            r += 8;
        }
    }
    return r;
}