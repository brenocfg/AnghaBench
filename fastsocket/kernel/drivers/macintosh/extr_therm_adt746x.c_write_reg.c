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
struct thermostat {int /*<<< orphan*/  clt; } ;

/* Variables and functions */
 int ENODEV ; 
 int i2c_master_send (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int
write_reg(struct thermostat* th, int reg, u8 data)
{
	u8 tmp[2];
	int rc;
	
	tmp[0] = reg;
	tmp[1] = data;
	rc = i2c_master_send(th->clt, (const char *)tmp, 2);
	if (rc < 0)
		return rc;
	if (rc != 2)
		return -ENODEV;
	return 0;
}