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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 scalar_t__ EX_TRAP ; 
 int raise_exception (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int opTRAP(Q68State *state, uint32_t opcode)
{
    return raise_exception(state, EX_TRAP + (opcode & 0x000F));
}