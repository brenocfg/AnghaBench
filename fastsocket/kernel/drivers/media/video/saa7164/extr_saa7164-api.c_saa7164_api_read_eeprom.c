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
struct saa7164_dev {int /*<<< orphan*/ * i2c_bus; } ;
typedef  int /*<<< orphan*/  reg ;

/* Variables and functions */
 int ENOMEM ; 
 int saa7164_api_i2c_read (int /*<<< orphan*/ *,int,int,int*,int,int*) ; 

int saa7164_api_read_eeprom(struct saa7164_dev *dev, u8 *buf, int buflen)
{
	u8 reg[] = { 0x0f, 0x00 };

	if (buflen < 128)
		return -ENOMEM;

	/* Assumption: Hauppauge eeprom is at 0xa0 on on bus 0 */
	/* TODO: Pull the details from the boards struct */
	return saa7164_api_i2c_read(&dev->i2c_bus[0], 0xa0 >> 1, sizeof(reg),
		&reg[0], 128, buf);
}