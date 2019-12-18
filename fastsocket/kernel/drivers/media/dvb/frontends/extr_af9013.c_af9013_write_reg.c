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
typedef  int /*<<< orphan*/  u16 ;
struct af9013_state {int dummy; } ;

/* Variables and functions */
 int af9013_write_ofdm_regs (struct af9013_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int af9013_write_reg(struct af9013_state *state, u16 reg, u8 val)
{
	return af9013_write_ofdm_regs(state, reg, &val, 1);
}