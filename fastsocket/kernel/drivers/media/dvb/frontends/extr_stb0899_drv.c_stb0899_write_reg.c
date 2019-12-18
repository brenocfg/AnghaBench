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
typedef  int /*<<< orphan*/  u8 ;
struct stb0899_state {int dummy; } ;

/* Variables and functions */
 int stb0899_write_regs (struct stb0899_state*,unsigned int,int /*<<< orphan*/ *,int) ; 

int stb0899_write_reg(struct stb0899_state *state, unsigned int reg, u8 data)
{
	return stb0899_write_regs(state, reg, &data, 1);
}