#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
typedef  int /*<<< orphan*/  Type ;
typedef  int /*<<< orphan*/  Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 char KDEFAULT ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/  make_pair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_vector () ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/ * peek () ; 
 int /*<<< orphan*/ * read_assignment_expr () ; 
 int /*<<< orphan*/ * read_cast_type () ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Vector *read_generic_list(Node **defaultexpr) {
    Vector *r = make_vector();
    for (;;) {
        if (next_token(')'))
            return r;
        Token *tok = peek();
        if (next_token(KDEFAULT)) {
            if (*defaultexpr)
                errort(tok, "default expression specified twice");
            expect(':');
            *defaultexpr = read_assignment_expr();
        } else {
            Type *ty = read_cast_type();
            expect(':');
            Node *expr = read_assignment_expr();
            vec_push(r, make_pair(ty, expr));
        }
        next_token(',');
    }
}