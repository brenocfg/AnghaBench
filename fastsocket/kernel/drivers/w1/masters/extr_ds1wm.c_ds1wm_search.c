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
typedef  int /*<<< orphan*/  (* w1_slave_found_callback ) (struct w1_master*,unsigned long long) ;
typedef  int /*<<< orphan*/  u8 ;
struct w1_master {int dummy; } ;
struct ds1wm_data {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1WM_CMD ; 
 int /*<<< orphan*/  DS1WM_CMD_SRA ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 unsigned char ds1wm_read (struct ds1wm_data*,int) ; 
 scalar_t__ ds1wm_reset (struct ds1wm_data*) ; 
 int /*<<< orphan*/  ds1wm_write (struct ds1wm_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1wm_write_register (struct ds1wm_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ds1wm_search(void *data, struct w1_master *master_dev,
			u8 search_type, w1_slave_found_callback slave_found)
{
	struct ds1wm_data *ds1wm_data = data;
	int i;
	unsigned long long rom_id;

	/* XXX We need to iterate for multiple devices per the DS1WM docs.
	 * See http://www.maxim-ic.com/appnotes.cfm/appnote_number/120. */
	if (ds1wm_reset(ds1wm_data))
		return;

	ds1wm_write(ds1wm_data, search_type);
	ds1wm_write_register(ds1wm_data, DS1WM_CMD, DS1WM_CMD_SRA);

	for (rom_id = 0, i = 0; i < 16; i++) {

		unsigned char resp, r, d;

		resp = ds1wm_read(ds1wm_data, 0x00);

		r = ((resp & 0x02) >> 1) |
		    ((resp & 0x08) >> 2) |
		    ((resp & 0x20) >> 3) |
		    ((resp & 0x80) >> 4);

		d = ((resp & 0x01) >> 0) |
		    ((resp & 0x04) >> 1) |
		    ((resp & 0x10) >> 2) |
		    ((resp & 0x40) >> 3);

		rom_id |= (unsigned long long) r << (i * 4);

	}
	dev_dbg(&ds1wm_data->pdev->dev, "found 0x%08llX\n", rom_id);

	ds1wm_write_register(ds1wm_data, DS1WM_CMD, ~DS1WM_CMD_SRA);
	ds1wm_reset(ds1wm_data);

	slave_found(master_dev, rom_id);
}