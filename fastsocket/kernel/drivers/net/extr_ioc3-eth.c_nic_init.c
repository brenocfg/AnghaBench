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
typedef  int u64 ;
struct ioc3 {int dummy; } ;

/* Variables and functions */
 int nic_find (struct ioc3*,int*) ; 
 int /*<<< orphan*/  nic_reset (struct ioc3*) ; 
 int /*<<< orphan*/  nic_write_byte (struct ioc3*,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int nic_init(struct ioc3 *ioc3)
{
	const char *unknown = "unknown";
	const char *type = unknown;
	u8 crc;
	u8 serial[6];
	int save = 0, i;

	while (1) {
		u64 reg;
		reg = nic_find(ioc3, &save);

		switch (reg & 0xff) {
		case 0x91:
			type = "DS1981U";
			break;
		default:
			if (save == 0) {
				/* Let the caller try again.  */
				return -1;
			}
			continue;
		}

		nic_reset(ioc3);

		/* Match ROM.  */
		nic_write_byte(ioc3, 0x55);
		for (i = 0; i < 8; i++)
			nic_write_byte(ioc3, (reg >> (i << 3)) & 0xff);

		reg >>= 8; /* Shift out type.  */
		for (i = 0; i < 6; i++) {
			serial[i] = reg & 0xff;
			reg >>= 8;
		}
		crc = reg & 0xff;
		break;
	}

	printk("Found %s NIC", type);
	if (type != unknown)
		printk (" registration number %pM, CRC %02x", serial, crc);
	printk(".\n");

	return 0;
}