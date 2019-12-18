#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct cx25821_dev {TYPE_1__* i2c_bus; } ;
typedef  int /*<<< orphan*/  eeprom ;
struct TYPE_4__ {int addr; } ;
struct TYPE_3__ {scalar_t__ i2c_rc; TYPE_2__ i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  tveeprom_read (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

void cx25821_card_setup(struct cx25821_dev *dev)
{
	static u8 eeprom[256];

	if (dev->i2c_bus[0].i2c_rc == 0) {
		dev->i2c_bus[0].i2c_client.addr = 0xa0 >> 1;
		tveeprom_read(&dev->i2c_bus[0].i2c_client, eeprom,
			      sizeof(eeprom));
	}
}