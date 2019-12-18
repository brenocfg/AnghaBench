#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_5__ {int /*<<< orphan*/  space; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 TYPE_1__* copy_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_head (int /*<<< orphan*/ *) ; 
 scalar_t__ vec_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void propagate_space(Vector *tokens, Token *tmpl) {
    if (vec_len(tokens) == 0)
        return;
    Token *tok = copy_token(vec_head(tokens));
    tok->space = tmpl->space;
    vec_set(tokens, 0, tok);
}