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

/* Variables and functions */
 scalar_t__ TNEWLINE ; 
 int /*<<< orphan*/  hashhash_check (int /*<<< orphan*/ *) ; 
 TYPE_1__* lex () ; 
 int /*<<< orphan*/  macros ; 
 int /*<<< orphan*/  make_obj_macro (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void read_obj_macro(char *name) {
    Vector *body = make_vector();
    for (;;) {
        Token *tok = lex();
        if (tok->kind == TNEWLINE)
            break;
        vec_push(body, tok);
    }
    hashhash_check(body);
    map_put(macros, name, make_obj_macro(body));
}