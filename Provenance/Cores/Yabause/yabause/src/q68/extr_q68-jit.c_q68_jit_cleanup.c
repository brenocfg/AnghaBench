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
struct TYPE_4__ {int /*<<< orphan*/ * jit_table; int /*<<< orphan*/  (* free_func ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * jit_hashchain; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  q68_jit_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

void q68_jit_cleanup(Q68State *state)
{
    q68_jit_reset(state);
    state->free_func(state->jit_hashchain);
    state->jit_hashchain = NULL;
    state->free_func(state->jit_table);
    state->jit_table = NULL;
}