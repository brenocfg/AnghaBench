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
typedef  int /*<<< orphan*/  Type ;
struct TYPE_5__ {int /*<<< orphan*/ * ty; int /*<<< orphan*/  stmts; } ;
typedef  TYPE_1__ Node ;

/* Variables and functions */
 int /*<<< orphan*/  expect (char) ; 
 TYPE_1__* read_compound_stmt () ; 
 int /*<<< orphan*/ * type_void ; 
 scalar_t__ vec_len (int /*<<< orphan*/ ) ; 
 TYPE_1__* vec_tail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *read_stmt_expr() {
    Node *r = read_compound_stmt();
    expect(')');
    Type *rtype = type_void;
    if (vec_len(r->stmts) > 0) {
        Node *lastexpr = vec_tail(r->stmts);
        if (lastexpr->ty)
            rtype = lastexpr->ty;
    }
    r->ty = rtype;
    return r;
}