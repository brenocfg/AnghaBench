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
struct TYPE_2__ {int /*<<< orphan*/  mchip_dmahandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCHIP_HIC_CMD ; 
 int /*<<< orphan*/  MCHIP_HIC_CMD_START ; 
 int /*<<< orphan*/  MCHIP_HIC_MODE ; 
 int /*<<< orphan*/  MCHIP_HIC_MODE_STILL_CAP ; 
 int /*<<< orphan*/  MCHIP_HIC_STATUS ; 
 int /*<<< orphan*/  MCHIP_HIC_STATUS_IDLE ; 
 scalar_t__ mchip_delay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchip_dma_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchip_hic_stop () ; 
 int /*<<< orphan*/  mchip_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mchip_subsample () ; 
 TYPE_1__ meye ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void mchip_take_picture(void)
{
	int i;

	mchip_hic_stop();
	mchip_subsample();
	mchip_dma_setup(meye.mchip_dmahandle);

	mchip_set(MCHIP_HIC_MODE, MCHIP_HIC_MODE_STILL_CAP);
	mchip_set(MCHIP_HIC_CMD, MCHIP_HIC_CMD_START);

	mchip_delay(MCHIP_HIC_CMD, 0);

	for (i = 0; i < 100; ++i) {
		if (mchip_delay(MCHIP_HIC_STATUS, MCHIP_HIC_STATUS_IDLE))
			break;
		msleep(1);
	}
}