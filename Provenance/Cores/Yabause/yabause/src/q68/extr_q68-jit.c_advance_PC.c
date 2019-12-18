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
struct TYPE_3__ {int current_PC; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  JIT_EMIT_ADVANCE_PC (int /*<<< orphan*/ ,int) ; 
 int PC_updated ; 
 int /*<<< orphan*/  current_entry ; 
 int jit_PC ; 

__attribute__((used)) static void advance_PC(Q68State *state)
{
    JIT_EMIT_ADVANCE_PC(current_entry, jit_PC - (state->current_PC - 2));
    PC_updated = 1;
}