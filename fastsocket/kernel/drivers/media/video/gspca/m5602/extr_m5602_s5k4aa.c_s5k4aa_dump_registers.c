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
struct sd {int dummy; } ;

/* Variables and functions */
 int S5K4AA_PAGE_MAP ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  m5602_read_sensor (struct sd*,int,int*,int) ; 
 int /*<<< orphan*/  m5602_write_sensor (struct sd*,int,int*,int) ; 

__attribute__((used)) static void s5k4aa_dump_registers(struct sd *sd)
{
	int address;
	u8 page, old_page;
	m5602_read_sensor(sd, S5K4AA_PAGE_MAP, &old_page, 1);
	for (page = 0; page < 16; page++) {
		m5602_write_sensor(sd, S5K4AA_PAGE_MAP, &page, 1);
		info("Dumping the s5k4aa register state for page 0x%x", page);
		for (address = 0; address <= 0xff; address++) {
			u8 value = 0;
			m5602_read_sensor(sd, address, &value, 1);
			info("register 0x%x contains 0x%x",
			     address, value);
		}
	}
	info("s5k4aa register state dump complete");

	for (page = 0; page < 16; page++) {
		m5602_write_sensor(sd, S5K4AA_PAGE_MAP, &page, 1);
		info("Probing for which registers that are "
		     "read/write for page 0x%x", page);
		for (address = 0; address <= 0xff; address++) {
			u8 old_value, ctrl_value, test_value = 0xff;

			m5602_read_sensor(sd, address, &old_value, 1);
			m5602_write_sensor(sd, address, &test_value, 1);
			m5602_read_sensor(sd, address, &ctrl_value, 1);

			if (ctrl_value == test_value)
				info("register 0x%x is writeable", address);
			else
				info("register 0x%x is read only", address);

			/* Restore original value */
			m5602_write_sensor(sd, address, &old_value, 1);
		}
	}
	info("Read/write register probing complete");
	m5602_write_sensor(sd, S5K4AA_PAGE_MAP, &old_page, 1);
}