#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* file; } ;
typedef  TYPE_2__ Token ;
struct TYPE_10__ {int /*<<< orphan*/  include_guard; TYPE_1__* file; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ CondIncl ;

/* Variables and functions */
 int /*<<< orphan*/  cond_incl_stack ; 
 int /*<<< orphan*/  errort (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  expect_newline () ; 
 int /*<<< orphan*/  include_guard ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* skip_newlines () ; 
 scalar_t__ vec_len (int /*<<< orphan*/ ) ; 
 TYPE_3__* vec_pop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_endif(Token *hash) {
    if (vec_len(cond_incl_stack) == 0)
        errort(hash, "stray #endif");
    CondIncl *ci = vec_pop(cond_incl_stack);
    expect_newline();

    // Detect an #ifndef and #endif pair that guards the entire
    // header file. Remember the macro name guarding the file
    // so that we can skip the file next time.
    if (!ci->include_guard || ci->file != hash->file)
        return;
    Token *last = skip_newlines();
    if (ci->file != last->file)
        map_put(include_guard, ci->file->name, ci->include_guard);
}