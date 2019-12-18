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
struct TYPE_4__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  KSTATIC_ASSERT ; 
 scalar_t__ TEOF ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ is_type (TYPE_1__*) ; 
 int /*<<< orphan*/  mark_location () ; 
 scalar_t__ next_token (int /*<<< orphan*/ ) ; 
 TYPE_1__* peek () ; 
 int /*<<< orphan*/  read_decl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_static_assert () ; 
 int /*<<< orphan*/ * read_stmt () ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_decl_or_stmt(Vector *list) {
    Token *tok = peek();
    if (tok->kind == TEOF)
        error("premature end of input");
    mark_location();
    if (is_type(tok)) {
        read_decl(list, false);
    } else if (next_token(KSTATIC_ASSERT)) {
        read_static_assert();
    } else {
        Node *stmt = read_stmt();
        if (stmt)
            vec_push(list, stmt);
    }
}