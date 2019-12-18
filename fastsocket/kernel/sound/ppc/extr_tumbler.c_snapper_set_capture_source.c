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
struct TYPE_2__ {int /*<<< orphan*/  client; } ;
struct pmac_tumbler {int acs; TYPE_1__ i2c; scalar_t__ capture_source; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  TAS_REG_ACS ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snapper_set_capture_source(struct pmac_tumbler *mix)
{
	if (! mix->i2c.client)
		return -ENODEV;
	if (mix->capture_source)
		mix->acs = mix->acs |= 2;
	else
		mix->acs &= ~2;
	return i2c_smbus_write_byte_data(mix->i2c.client, TAS_REG_ACS, mix->acs);
}