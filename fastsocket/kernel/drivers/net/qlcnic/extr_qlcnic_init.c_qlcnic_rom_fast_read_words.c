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
typedef  int /*<<< orphan*/  u8 ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int do_rom_fast_read_words (struct qlcnic_adapter*,int,int /*<<< orphan*/ *,size_t) ; 
 int qlcnic_rom_lock (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_rom_unlock (struct qlcnic_adapter*) ; 

int
qlcnic_rom_fast_read_words(struct qlcnic_adapter *adapter, int addr,
				u8 *bytes, size_t size)
{
	int ret;

	ret = qlcnic_rom_lock(adapter);
	if (ret < 0)
		return ret;

	ret = do_rom_fast_read_words(adapter, addr, bytes, size);

	qlcnic_rom_unlock(adapter);
	return ret;
}