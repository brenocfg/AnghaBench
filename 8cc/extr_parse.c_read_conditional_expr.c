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
 int /*<<< orphan*/ * do_read_conditional_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_token (char) ; 
 int /*<<< orphan*/ * read_logor_expr () ; 

__attribute__((used)) static Node *read_conditional_expr() {
    Node *cond = read_logor_expr();
    if (!next_token('?'))
        return cond;
    return do_read_conditional_expr(cond);
}