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

/* Variables and functions */
 int /*<<< orphan*/  WORDSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_relations () ; 
 int /*<<< orphan*/  compute_FOLLOWS () ; 
 int /*<<< orphan*/  compute_lookaheads () ; 
 int /*<<< orphan*/  initialize_F () ; 
 int /*<<< orphan*/  initialize_LA () ; 
 int /*<<< orphan*/  ntokens ; 
 int /*<<< orphan*/  set_accessing_symbol () ; 
 int /*<<< orphan*/  set_goto_map () ; 
 int /*<<< orphan*/  set_maxrhs () ; 
 int /*<<< orphan*/  set_reduction_table () ; 
 int /*<<< orphan*/  set_shift_table () ; 
 int /*<<< orphan*/  set_state_table () ; 
 int /*<<< orphan*/  tokensetsize ; 

void
lalr(void)
{
    tokensetsize = WORDSIZE(ntokens);

    set_state_table();
    set_accessing_symbol();
    set_shift_table();
    set_reduction_table();
    set_maxrhs();
    initialize_LA();
    set_goto_map();
    initialize_F();
    build_relations();
    compute_FOLLOWS();
    compute_lookaheads();
}