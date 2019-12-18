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
struct cb710_slot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB710_MMC_C1_4BIT_DATA_BUS ; 
 int /*<<< orphan*/  CB710_MMC_CONFIG1_PORT ; 
 int /*<<< orphan*/  cb710_modify_port_8 (struct cb710_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_slot_dev (struct cb710_slot*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,char*) ; 

__attribute__((used)) static void cb710_mmc_enable_4bit_data(struct cb710_slot *slot, int enable)
{
	dev_dbg(cb710_slot_dev(slot), "configuring %d-data-line%s mode\n",
		enable ? 4 : 1, enable ? "s" : "");
	if (enable)
		cb710_modify_port_8(slot, CB710_MMC_CONFIG1_PORT,
			CB710_MMC_C1_4BIT_DATA_BUS, 0);
	else
		cb710_modify_port_8(slot, CB710_MMC_CONFIG1_PORT,
			0, CB710_MMC_C1_4BIT_DATA_BUS);
}