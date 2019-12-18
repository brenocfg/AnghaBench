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
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/  read_decl_or_stmt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *read_opt_decl_or_stmt() {
    if (next_token(';'))
        return NULL;
    Vector *list = make_vector();
    read_decl_or_stmt(list);
    return ast_compound_stmt(list);
}