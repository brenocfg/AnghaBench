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
struct ds1wm_data {TYPE_1__* pdev; int /*<<< orphan*/  slave_present; scalar_t__ active_high; int /*<<< orphan*/ * reset_complete; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DS1WM_CMD ; 
 int DS1WM_CMD_1W_RESET ; 
 int DS1WM_INTEN_EPD ; 
 int DS1WM_INTEN_ERBF ; 
 int DS1WM_INTEN_ETMT ; 
 int DS1WM_INTEN_IAS ; 
 int /*<<< orphan*/  DS1WM_INT_EN ; 
 int /*<<< orphan*/  DS1WM_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ds1wm_write_register (struct ds1wm_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reset_done ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds1wm_reset(struct ds1wm_data *ds1wm_data)
{
	unsigned long timeleft;
	DECLARE_COMPLETION_ONSTACK(reset_done);

	ds1wm_data->reset_complete = &reset_done;

	ds1wm_write_register(ds1wm_data, DS1WM_INT_EN, DS1WM_INTEN_EPD |
		(ds1wm_data->active_high ? DS1WM_INTEN_IAS : 0));

	ds1wm_write_register(ds1wm_data, DS1WM_CMD, DS1WM_CMD_1W_RESET);

	timeleft = wait_for_completion_timeout(&reset_done, DS1WM_TIMEOUT);
	ds1wm_data->reset_complete = NULL;
	if (!timeleft) {
		dev_err(&ds1wm_data->pdev->dev, "reset failed\n");
		return 1;
	}

	/* Wait for the end of the reset. According to the specs, the time
	 * from when the interrupt is asserted to the end of the reset is:
	 *     tRSTH  - tPDH  - tPDL - tPDI
	 *     625 us - 60 us - 240 us - 100 ns = 324.9 us
	 *
	 * We'll wait a bit longer just to be sure.
	 * Was udelay(500), but if it is going to busywait the cpu that long,
	 * might as well come back later.
	 */
	msleep(1);

	ds1wm_write_register(ds1wm_data, DS1WM_INT_EN,
		DS1WM_INTEN_ERBF | DS1WM_INTEN_ETMT | DS1WM_INTEN_EPD |
		(ds1wm_data->active_high ? DS1WM_INTEN_IAS : 0));

	if (!ds1wm_data->slave_present) {
		dev_dbg(&ds1wm_data->pdev->dev, "reset: no devices found\n");
		return 1;
	}

	return 0;
}