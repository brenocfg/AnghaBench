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
typedef  int /*<<< orphan*/  uint8_t ;
struct qla_hw_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_OEM_001 (struct qla_hw_data*) ; 
 int qla2x00_poll_flash (struct qla_hw_data*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_write_flash_byte (struct qla_hw_data*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
qla2x00_erase_flash(struct qla_hw_data *ha, uint8_t man_id, uint8_t flash_id)
{
	/* Individual Sector Erase Command Sequence */
	if (IS_OEM_001(ha)) {
		qla2x00_write_flash_byte(ha, 0xaaa, 0xaa);
		qla2x00_write_flash_byte(ha, 0x555, 0x55);
		qla2x00_write_flash_byte(ha, 0xaaa, 0x80);
		qla2x00_write_flash_byte(ha, 0xaaa, 0xaa);
		qla2x00_write_flash_byte(ha, 0x555, 0x55);
		qla2x00_write_flash_byte(ha, 0xaaa, 0x10);
	} else {
		qla2x00_write_flash_byte(ha, 0x5555, 0xaa);
		qla2x00_write_flash_byte(ha, 0x2aaa, 0x55);
		qla2x00_write_flash_byte(ha, 0x5555, 0x80);
		qla2x00_write_flash_byte(ha, 0x5555, 0xaa);
		qla2x00_write_flash_byte(ha, 0x2aaa, 0x55);
		qla2x00_write_flash_byte(ha, 0x5555, 0x10);
	}

	udelay(150);

	/* Wait for erase to complete. */
	return qla2x00_poll_flash(ha, 0x00, 0x80, man_id, flash_id);
}