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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct af9013_state {int dummy; } ;

/* Variables and functions */
 int af9013_read_reg (struct af9013_state*,int /*<<< orphan*/ ,int*) ; 
 int af9013_write_reg (struct af9013_state*,int /*<<< orphan*/ ,int) ; 
 int* regmask ; 

__attribute__((used)) static int af9013_write_reg_bits(struct af9013_state *state, u16 reg, u8 pos,
	u8 len, u8 val)
{
	int ret;
	u8 tmp, mask;

	ret = af9013_read_reg(state, reg, &tmp);
	if (ret)
		return ret;

	mask = regmask[len - 1] << pos;
	tmp = (tmp & ~mask) | ((val << pos) & mask);

	return af9013_write_reg(state, reg, tmp);
}