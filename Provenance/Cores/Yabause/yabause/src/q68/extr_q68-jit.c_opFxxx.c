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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  EX_LINE_1111 ; 
 int raise_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opFxxx(Q68State *state, uint32_t opcode)
{
    return raise_exception(state, EX_LINE_1111);
}