#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ kind; int count; int /*<<< orphan*/  file; int /*<<< orphan*/  sval; } ;
typedef  TYPE_1__ Token ;
struct TYPE_8__ {int /*<<< orphan*/  file; int /*<<< orphan*/  include_guard; } ;
typedef  TYPE_2__ CondIncl ;

/* Variables and functions */
 scalar_t__ TIDENT ; 
 int /*<<< orphan*/  cond_incl_stack ; 
 int /*<<< orphan*/  do_read_if (int) ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_newline () ; 
 TYPE_1__* lex () ; 
 int /*<<< orphan*/  macros ; 
 int /*<<< orphan*/  map_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 
 TYPE_2__* vec_tail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_ifndef() {
    Token *tok = lex();
    if (tok->kind != TIDENT)
        errort(tok, "identifier expected, but got %s", tok2s(tok));
    expect_newline();
    do_read_if(!map_get(macros, tok->sval));
    if (tok->count == 2) {
        // "ifndef" is the second token in this file.
        // Prepare to detect an include guard.
        CondIncl *ci = vec_tail(cond_incl_stack);
        ci->include_guard = tok->sval;
        ci->file = tok->file;
    }
}