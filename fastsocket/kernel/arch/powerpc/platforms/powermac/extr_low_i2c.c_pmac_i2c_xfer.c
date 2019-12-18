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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pmac_i2c_bus {int (* xfer ) (struct pmac_i2c_bus*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;TYPE_1__* busnode; int /*<<< orphan*/  mode; int /*<<< orphan*/  channel; int /*<<< orphan*/  opened; } ;
struct TYPE_2__ {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,...) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int stub1 (struct pmac_i2c_bus*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int pmac_i2c_xfer(struct pmac_i2c_bus *bus, u8 addrdir, int subsize,
		  u32 subaddr, u8 *data, int len)
{
	int rc;

	WARN_ON(!bus->opened);

	DBG("xfer() chan=%d, addrdir=0x%x, mode=%d, subsize=%d, subaddr=0x%x,"
	    " %d bytes, bus %s\n", bus->channel, addrdir, bus->mode, subsize,
	    subaddr, len, bus->busnode->full_name);

	rc = bus->xfer(bus, addrdir, subsize, subaddr, data, len);

#ifdef DEBUG
	if (rc)
		DBG("xfer error %d\n", rc);
#endif
	return rc;
}