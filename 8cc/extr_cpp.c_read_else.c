#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Token ;
struct TYPE_3__ {scalar_t__ ctx; scalar_t__ wastrue; int /*<<< orphan*/ * include_guard; } ;
typedef  TYPE_1__ CondIncl ;

/* Variables and functions */
 scalar_t__ IN_ELSE ; 
 int /*<<< orphan*/  cond_incl_stack ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  expect_newline () ; 
 int /*<<< orphan*/  skip_cond_incl () ; 
 scalar_t__ vec_len (int /*<<< orphan*/ ) ; 
 TYPE_1__* vec_tail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_else(Token *hash) {
    if (vec_len(cond_incl_stack) == 0)
        errort(hash, "stray #else");
    CondIncl *ci = vec_tail(cond_incl_stack);
    if (ci->ctx == IN_ELSE)
        errort(hash, "#else appears in #else");
    expect_newline();
    ci->ctx = IN_ELSE;
    ci->include_guard = NULL;
    if (ci->wastrue)
        skip_cond_incl();
}