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
typedef  int /*<<< orphan*/  Token ;
struct TYPE_4__ {scalar_t__ nargs; } ;
typedef  TYPE_1__ Macro ;

/* Variables and functions */
 int /*<<< orphan*/ * do_read_args (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/  peek_token () ; 
 scalar_t__ vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Vector *read_args(Token *tok, Macro *macro) {
    if (macro->nargs == 0 && is_keyword(peek_token(), ')')) {
        // If a macro M has no parameter, argument list of M()
        // is an empty list. If it has one parameter,
        // argument list of M() is a list containing an empty list.
        return make_vector();
    }
    Vector *args = do_read_args(tok, macro);
    if (vec_len(args) != macro->nargs)
        errort(tok, "macro argument number does not match");
    return args;
}