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
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  KELSE ; 
 int /*<<< orphan*/ * ast_if (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/  next_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_boolean_expr () ; 
 int /*<<< orphan*/ * read_stmt () ; 

__attribute__((used)) static Node *read_if_stmt() {
    expect('(');
    Node *cond = read_boolean_expr();
    expect(')');
    Node *then = read_stmt();
    if (!next_token(KELSE))
        return ast_if(cond, then, NULL);
    Node *els = read_stmt();
    return ast_if(cond, then, els);
}