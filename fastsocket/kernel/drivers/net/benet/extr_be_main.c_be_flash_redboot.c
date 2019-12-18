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
typedef  scalar_t__ u32 ;
struct be_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int be_cmd_get_flash_crc (struct be_adapter*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static bool be_flash_redboot(struct be_adapter *adapter,
			const u8 *p, u32 img_start, int image_size,
			int hdr_size)
{
	u32 crc_offset;
	u8 flashed_crc[4];
	int status;

	crc_offset = hdr_size + img_start + image_size - 4;

	p += crc_offset;

	status = be_cmd_get_flash_crc(adapter, flashed_crc,
			(image_size - 4));
	if (status) {
		dev_err(&adapter->pdev->dev,
		"could not get crc from flash, not flashing redboot\n");
		return false;
	}

	/*update redboot only if crc does not match*/
	if (!memcmp(flashed_crc, p, 4))
		return false;
	else
		return true;
}