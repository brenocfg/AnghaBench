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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int CNTRL_TFE ; 
 int CNTRL_TXE ; 
 int /*<<< orphan*/  CX25840_IR_CNTRL_REG ; 
 int /*<<< orphan*/  cx25840_and_or4 (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void control_tx_enable(struct i2c_client *c, bool enable)
{
	cx25840_and_or4(c, CX25840_IR_CNTRL_REG, ~(CNTRL_TXE | CNTRL_TFE),
			enable ? (CNTRL_TXE | CNTRL_TFE) : 0);
}