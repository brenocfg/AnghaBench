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
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * ast_compound_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/ * read_stmt () ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *read_label_tail(Node *label) {
    Node *stmt = read_stmt();
    Vector *v = make_vector();
    vec_push(v, label);
    if (stmt)
        vec_push(v, stmt);
    return ast_compound_stmt(v);
}