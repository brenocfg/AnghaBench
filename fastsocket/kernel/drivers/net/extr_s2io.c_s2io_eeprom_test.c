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
typedef  int uint64_t ;
typedef  int u8 ;
typedef  int u64 ;
struct s2io_nic {scalar_t__ device_type; struct net_device* dev; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  ERR_DBG ; 
 scalar_t__ XFRAME_I_DEVICE ; 
 scalar_t__ read_eeprom (struct s2io_nic*,int,int*) ; 
 int /*<<< orphan*/  write_eeprom (struct s2io_nic*,int,int,int) ; 

__attribute__((used)) static int s2io_eeprom_test(struct s2io_nic *sp, uint64_t *data)
{
	int fail = 0;
	u64 ret_data, org_4F0, org_7F0;
	u8 saved_4F0 = 0, saved_7F0 = 0;
	struct net_device *dev = sp->dev;

	/* Test Write Error at offset 0 */
	/* Note that SPI interface allows write access to all areas
	 * of EEPROM. Hence doing all negative testing only for Xframe I.
	 */
	if (sp->device_type == XFRAME_I_DEVICE)
		if (!write_eeprom(sp, 0, 0, 3))
			fail = 1;

	/* Save current values at offsets 0x4F0 and 0x7F0 */
	if (!read_eeprom(sp, 0x4F0, &org_4F0))
		saved_4F0 = 1;
	if (!read_eeprom(sp, 0x7F0, &org_7F0))
		saved_7F0 = 1;

	/* Test Write at offset 4f0 */
	if (write_eeprom(sp, 0x4F0, 0x012345, 3))
		fail = 1;
	if (read_eeprom(sp, 0x4F0, &ret_data))
		fail = 1;

	if (ret_data != 0x012345) {
		DBG_PRINT(ERR_DBG, "%s: eeprom test error at offset 0x4F0. "
			  "Data written %llx Data read %llx\n",
			  dev->name, (unsigned long long)0x12345,
			  (unsigned long long)ret_data);
		fail = 1;
	}

	/* Reset the EEPROM data go FFFF */
	write_eeprom(sp, 0x4F0, 0xFFFFFF, 3);

	/* Test Write Request Error at offset 0x7c */
	if (sp->device_type == XFRAME_I_DEVICE)
		if (!write_eeprom(sp, 0x07C, 0, 3))
			fail = 1;

	/* Test Write Request at offset 0x7f0 */
	if (write_eeprom(sp, 0x7F0, 0x012345, 3))
		fail = 1;
	if (read_eeprom(sp, 0x7F0, &ret_data))
		fail = 1;

	if (ret_data != 0x012345) {
		DBG_PRINT(ERR_DBG, "%s: eeprom test error at offset 0x7F0. "
			  "Data written %llx Data read %llx\n",
			  dev->name, (unsigned long long)0x12345,
			  (unsigned long long)ret_data);
		fail = 1;
	}

	/* Reset the EEPROM data go FFFF */
	write_eeprom(sp, 0x7F0, 0xFFFFFF, 3);

	if (sp->device_type == XFRAME_I_DEVICE) {
		/* Test Write Error at offset 0x80 */
		if (!write_eeprom(sp, 0x080, 0, 3))
			fail = 1;

		/* Test Write Error at offset 0xfc */
		if (!write_eeprom(sp, 0x0FC, 0, 3))
			fail = 1;

		/* Test Write Error at offset 0x100 */
		if (!write_eeprom(sp, 0x100, 0, 3))
			fail = 1;

		/* Test Write Error at offset 4ec */
		if (!write_eeprom(sp, 0x4EC, 0, 3))
			fail = 1;
	}

	/* Restore values at offsets 0x4F0 and 0x7F0 */
	if (saved_4F0)
		write_eeprom(sp, 0x4F0, org_4F0, 3);
	if (saved_7F0)
		write_eeprom(sp, 0x7F0, org_7F0, 3);

	*data = fail;
	return fail;
}