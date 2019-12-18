#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_13__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;
struct TYPE_15__ {scalar_t__ kind; } ;
struct TYPE_14__ {TYPE_6__* ty; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 TYPE_2__* ast_conv (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ast_init (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* conv (int /*<<< orphan*/ ) ; 
 scalar_t__ is_arithtype (TYPE_6__*) ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ ,char) ; 
 scalar_t__ is_string (TYPE_1__*) ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/  peek () ; 
 int /*<<< orphan*/  read_assignment_expr () ; 
 int /*<<< orphan*/  read_initializer_list (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Vector *read_decl_init(Type *ty) {
    Vector *r = make_vector();
    if (is_keyword(peek(), '{') || is_string(ty)) {
        read_initializer_list(r, ty, 0, false);
    } else {
        Node *init = conv(read_assignment_expr());
        if (is_arithtype(init->ty) && init->ty->kind != ty->kind)
            init = ast_conv(ty, init);
        vec_push(r, ast_init(init, ty, 0));
    }
    return r;
}