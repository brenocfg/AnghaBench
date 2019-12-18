#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_9__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;
struct TYPE_10__ {int /*<<< orphan*/  ty; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 scalar_t__ KIND_ARRAY ; 
 scalar_t__ KIND_STRUCT ; 
 int /*<<< orphan*/  ast_init (TYPE_2__*,TYPE_1__*,int) ; 
 TYPE_2__* conv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_assignable (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (char) ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/  read_assignment_expr () ; 
 int /*<<< orphan*/  read_initializer_list (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_initializer_elem(Vector *inits, Type *ty, int off, bool designated) {
    next_token('=');
    if (ty->kind == KIND_ARRAY || ty->kind == KIND_STRUCT) {
        read_initializer_list(inits, ty, off, designated);
    } else if (next_token('{')) {
        read_initializer_elem(inits, ty, off, true);
        expect('}');
    } else {
        Node *expr = conv(read_assignment_expr());
        ensure_assignable(ty, expr->ty);
        vec_push(inits, ast_init(expr, ty, off));
    }
}