#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9P012_REG_RESET_REGISTER ; 
 int /*<<< orphan*/  MT9P012_RESET_REGISTER_PWOFF ; 
 int /*<<< orphan*/  mdelay (int) ; 
 TYPE_1__* mt9p012_client ; 
 int /*<<< orphan*/  mt9p012_i2c_write_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t mt9p012_power_down(void)
{
	int32_t rc = 0;

	rc = mt9p012_i2c_write_w(mt9p012_client->addr,
		MT9P012_REG_RESET_REGISTER,
		MT9P012_RESET_REGISTER_PWOFF);

	mdelay(5);
	return rc;
}