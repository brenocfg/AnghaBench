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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct qla_hw_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ LSB (int) ; 
 scalar_t__ MSB (int) ; 
 int /*<<< orphan*/  flash_conf_addr (struct qla_hw_data*,int) ; 
 int qla24xx_read_flash_dword (struct qla_hw_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla24xx_get_flash_manufacturer(struct qla_hw_data *ha, uint8_t *man_id,
    uint8_t *flash_id)
{
	uint32_t ids;

	ids = qla24xx_read_flash_dword(ha, flash_conf_addr(ha, 0x03ab));
	*man_id = LSB(ids);
	*flash_id = MSB(ids);

	/* Check if man_id and flash_id are valid. */
	if (ids != 0xDEADDEAD && (*man_id == 0 || *flash_id == 0)) {
		/* Read information using 0x9f opcode
		 * Device ID, Mfg ID would be read in the format:
		 *   <Ext Dev Info><Device ID Part2><Device ID Part 1><Mfg ID>
		 * Example: ATMEL 0x00 01 45 1F
		 * Extract MFG and Dev ID from last two bytes.
		 */
		ids = qla24xx_read_flash_dword(ha, flash_conf_addr(ha, 0x009f));
		*man_id = LSB(ids);
		*flash_id = MSB(ids);
	}
}