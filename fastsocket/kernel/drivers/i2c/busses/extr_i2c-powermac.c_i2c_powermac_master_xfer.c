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
struct pmac_i2c_bus {int dummy; } ;
struct i2c_msg {int flags; int addr; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2C_M_RD ; 
 int I2C_M_REV_DIR_ADDR ; 
 int I2C_M_TEN ; 
 struct pmac_i2c_bus* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  pmac_i2c_close (struct pmac_i2c_bus*) ; 
 int /*<<< orphan*/  pmac_i2c_mode_std ; 
 int pmac_i2c_open (struct pmac_i2c_bus*,int /*<<< orphan*/ ) ; 
 int pmac_i2c_setmode (struct pmac_i2c_bus*,int /*<<< orphan*/ ) ; 
 int pmac_i2c_xfer (struct pmac_i2c_bus*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_powermac_master_xfer(	struct i2c_adapter *adap,
					struct i2c_msg *msgs,
					int num)
{
	struct pmac_i2c_bus	*bus = i2c_get_adapdata(adap);
	int			rc = 0;
	int			read;
	int			addrdir;

	if (msgs->flags & I2C_M_TEN)
		return -EINVAL;
	read = (msgs->flags & I2C_M_RD) != 0;
	addrdir = (msgs->addr << 1) | read;
	if (msgs->flags & I2C_M_REV_DIR_ADDR)
		addrdir ^= 1;

	rc = pmac_i2c_open(bus, 0);
	if (rc)
		return rc;
	rc = pmac_i2c_setmode(bus, pmac_i2c_mode_std);
	if (rc)
		goto bail;
	rc = pmac_i2c_xfer(bus, addrdir, 0, 0, msgs->buf, msgs->len);
 bail:
	pmac_i2c_close(bus);
	return rc < 0 ? rc : 1;
}