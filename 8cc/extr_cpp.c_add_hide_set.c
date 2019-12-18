#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_4__ {int /*<<< orphan*/  hideset; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Set ;

/* Variables and functions */
 TYPE_1__* copy_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/  set_union (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_get (int /*<<< orphan*/ *,int) ; 
 int vec_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Vector *add_hide_set(Vector *tokens, Set *hideset) {
    Vector *r = make_vector();
    for (int i = 0; i < vec_len(tokens); i++) {
        Token *t = copy_token(vec_get(tokens, i));
        t->hideset = set_union(t->hideset, hideset);
        vec_push(r, t);
    }
    return r;
}