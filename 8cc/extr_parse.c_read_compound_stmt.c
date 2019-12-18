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
typedef  int /*<<< orphan*/  Map ;

/* Variables and functions */
 int /*<<< orphan*/ * ast_compound_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * localenv ; 
 int /*<<< orphan*/ * make_map_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_vector () ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/  read_decl_or_stmt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *read_compound_stmt() {
    Map *orig = localenv;
    localenv = make_map_parent(localenv);
    Vector *list = make_vector();
    for (;;) {
        if (next_token('}'))
            break;
        read_decl_or_stmt(list);
    }
    localenv = orig;
    return ast_compound_stmt(list);
}