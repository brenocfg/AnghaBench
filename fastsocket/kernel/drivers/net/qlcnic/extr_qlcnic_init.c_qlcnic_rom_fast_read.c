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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int do_rom_fast_read (struct qlcnic_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ qlcnic_rom_lock (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_rom_unlock (struct qlcnic_adapter*) ; 

int qlcnic_rom_fast_read(struct qlcnic_adapter *adapter, u32 addr, u32 *valp)
{
	int ret;

	if (qlcnic_rom_lock(adapter) != 0)
		return -EIO;

	ret = do_rom_fast_read(adapter, addr, valp);
	qlcnic_rom_unlock(adapter);
	return ret;
}