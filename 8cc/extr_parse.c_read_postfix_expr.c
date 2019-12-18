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
 int /*<<< orphan*/ * read_postfix_expr_tail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_primary_expr () ; 

__attribute__((used)) static Node *read_postfix_expr() {
    Node *node = read_primary_expr();
    return read_postfix_expr_tail(node);
}