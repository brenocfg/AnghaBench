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
struct sca3000_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCA3000_REG_ADDR_CTRL_DATA ; 
 int /*<<< orphan*/  SCA3000_REG_ADDR_CTRL_SEL ; 
 int __sca3000_unlock_reg_lock (struct sca3000_state*) ; 
 int sca3000_read_data (struct sca3000_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int sca3000_reg_lock_on (struct sca3000_state*) ; 
 int sca3000_write_reg (struct sca3000_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sca3000_read_ctrl_reg(struct sca3000_state *st,
				 u8 ctrl_reg,
				 u8 **rx_p)
{
	int ret;

	ret = sca3000_reg_lock_on(st);
	if (ret < 0)
		goto error_ret;
	if (ret) {
		ret = __sca3000_unlock_reg_lock(st);
		if (ret)
			goto error_ret;
	}
	/* Set the control select register */
	ret = sca3000_write_reg(st, SCA3000_REG_ADDR_CTRL_SEL, ctrl_reg);
	if (ret)
		goto error_ret;
	ret = sca3000_read_data(st, SCA3000_REG_ADDR_CTRL_DATA, rx_p, 1);

error_ret:
	return ret;
}