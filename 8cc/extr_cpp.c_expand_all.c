#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_6__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ TEOF ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/  propagate_space (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* read_expand () ; 
 int /*<<< orphan*/  token_buffer_stash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  token_buffer_unstash () ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vec_reverse (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Vector *expand_all(Vector *tokens, Token *tmpl) {
    token_buffer_stash(vec_reverse(tokens));
    Vector *r = make_vector();
    for (;;) {
        Token *tok = read_expand();
        if (tok->kind == TEOF)
            break;
        vec_push(r, tok);
    }
    propagate_space(r, tmpl);
    token_buffer_unstash();
    return r;
}