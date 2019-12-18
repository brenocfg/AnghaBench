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
typedef  int /*<<< orphan*/  Map ;

/* Variables and functions */
 int /*<<< orphan*/  errort (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  is_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * localenv ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/  peek () ; 
 int /*<<< orphan*/  read_decl (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tok2s (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Vector *read_oldstyle_param_args() {
    Map *orig = localenv;
    localenv = NULL;
    Vector *r = make_vector();
    for (;;) {
        if (is_keyword(peek(), '{'))
            break;
        if (!is_type(peek()))
            errort(peek(), "K&R-style declarator expected, but got %s", tok2s(peek()));
        read_decl(r, false);
    }
    localenv = orig;
    return r;
}