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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct qla_hw_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_OEM_001 (struct qla_hw_data*) ; 
 int qla2x00_poll_flash (struct qla_hw_data*,int,int,int,int) ; 
 int /*<<< orphan*/  qla2x00_write_flash_byte (struct qla_hw_data*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
qla2x00_program_flash_address(struct qla_hw_data *ha, uint32_t addr,
    uint8_t data, uint8_t man_id, uint8_t flash_id)
{
	/* Write Program Command Sequence. */
	if (IS_OEM_001(ha)) {
		qla2x00_write_flash_byte(ha, 0xaaa, 0xaa);
		qla2x00_write_flash_byte(ha, 0x555, 0x55);
		qla2x00_write_flash_byte(ha, 0xaaa, 0xa0);
		qla2x00_write_flash_byte(ha, addr, data);
	} else {
		if (man_id == 0xda && flash_id == 0xc1) {
			qla2x00_write_flash_byte(ha, addr, data);
			if (addr & 0x7e)
				return 0;
		} else {
			qla2x00_write_flash_byte(ha, 0x5555, 0xaa);
			qla2x00_write_flash_byte(ha, 0x2aaa, 0x55);
			qla2x00_write_flash_byte(ha, 0x5555, 0xa0);
			qla2x00_write_flash_byte(ha, addr, data);
		}
	}

	udelay(150);

	/* Wait for write to complete. */
	return qla2x00_poll_flash(ha, addr, data, man_id, flash_id);
}