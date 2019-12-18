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
typedef  int u8 ;
typedef  int u32 ;
struct nes_device {int dummy; } ;

/* Variables and functions */
 int NE020_REV ; 
 int /*<<< orphan*/  NES_DBG_INIT ; 
 int NES_IDX_WQM_CONFIG1 ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,int) ; 
 int nes_read_indexed (struct nes_device*,int) ; 
 int /*<<< orphan*/  nes_write_indexed (struct nes_device*,int,int) ; 
 int wqm_quanta ; 

__attribute__((used)) static void nes_init_csr_ne020(struct nes_device *nesdev, u8 hw_rev, u8 port_count)
{
	u32 u32temp;

	nes_debug(NES_DBG_INIT, "port_count=%d\n", port_count);

	nes_write_indexed(nesdev, 0x000001E4, 0x00000007);
	/* nes_write_indexed(nesdev, 0x000001E8, 0x000208C4); */
	nes_write_indexed(nesdev, 0x000001E8, 0x00020874);
	nes_write_indexed(nesdev, 0x000001D8, 0x00048002);
	/* nes_write_indexed(nesdev, 0x000001D8, 0x0004B002); */
	nes_write_indexed(nesdev, 0x000001FC, 0x00050005);
	nes_write_indexed(nesdev, 0x00000600, 0x55555555);
	nes_write_indexed(nesdev, 0x00000604, 0x55555555);

	/* TODO: move these MAC register settings to NIC bringup */
	nes_write_indexed(nesdev, 0x00002000, 0x00000001);
	nes_write_indexed(nesdev, 0x00002004, 0x00000001);
	nes_write_indexed(nesdev, 0x00002008, 0x0000FFFF);
	nes_write_indexed(nesdev, 0x0000200C, 0x00000001);
	nes_write_indexed(nesdev, 0x00002010, 0x000003c1);
	nes_write_indexed(nesdev, 0x0000201C, 0x75345678);
	if (port_count > 1) {
		nes_write_indexed(nesdev, 0x00002200, 0x00000001);
		nes_write_indexed(nesdev, 0x00002204, 0x00000001);
		nes_write_indexed(nesdev, 0x00002208, 0x0000FFFF);
		nes_write_indexed(nesdev, 0x0000220C, 0x00000001);
		nes_write_indexed(nesdev, 0x00002210, 0x000003c1);
		nes_write_indexed(nesdev, 0x0000221C, 0x75345678);
		nes_write_indexed(nesdev, 0x00000908, 0x20000001);
	}
	if (port_count > 2) {
		nes_write_indexed(nesdev, 0x00002400, 0x00000001);
		nes_write_indexed(nesdev, 0x00002404, 0x00000001);
		nes_write_indexed(nesdev, 0x00002408, 0x0000FFFF);
		nes_write_indexed(nesdev, 0x0000240C, 0x00000001);
		nes_write_indexed(nesdev, 0x00002410, 0x000003c1);
		nes_write_indexed(nesdev, 0x0000241C, 0x75345678);
		nes_write_indexed(nesdev, 0x00000910, 0x20000001);

		nes_write_indexed(nesdev, 0x00002600, 0x00000001);
		nes_write_indexed(nesdev, 0x00002604, 0x00000001);
		nes_write_indexed(nesdev, 0x00002608, 0x0000FFFF);
		nes_write_indexed(nesdev, 0x0000260C, 0x00000001);
		nes_write_indexed(nesdev, 0x00002610, 0x000003c1);
		nes_write_indexed(nesdev, 0x0000261C, 0x75345678);
		nes_write_indexed(nesdev, 0x00000918, 0x20000001);
	}

	nes_write_indexed(nesdev, 0x00005000, 0x00018000);
	/* nes_write_indexed(nesdev, 0x00005000, 0x00010000); */
	nes_write_indexed(nesdev, NES_IDX_WQM_CONFIG1, (wqm_quanta << 1) |
							 0x00000001);
	nes_write_indexed(nesdev, 0x00005008, 0x1F1F1F1F);
	nes_write_indexed(nesdev, 0x00005010, 0x1F1F1F1F);
	nes_write_indexed(nesdev, 0x00005018, 0x1F1F1F1F);
	nes_write_indexed(nesdev, 0x00005020, 0x1F1F1F1F);
	nes_write_indexed(nesdev, 0x00006090, 0xFFFFFFFF);

	/* TODO: move this to code, get from EEPROM */
	nes_write_indexed(nesdev, 0x00000900, 0x20000001);
	nes_write_indexed(nesdev, 0x000060C0, 0x0000028e);
	nes_write_indexed(nesdev, 0x000060C8, 0x00000020);

	nes_write_indexed(nesdev, 0x000001EC, 0x7b2625a0);
	/* nes_write_indexed(nesdev, 0x000001EC, 0x5f2625a0); */

	if (hw_rev != NE020_REV) {
		u32temp = nes_read_indexed(nesdev, 0x000008e8);
		u32temp |= 0x80000000;
		nes_write_indexed(nesdev, 0x000008e8, u32temp);
		u32temp = nes_read_indexed(nesdev, 0x000021f8);
		u32temp &= 0x7fffffff;
		u32temp |= 0x7fff0010;
		nes_write_indexed(nesdev, 0x000021f8, u32temp);
		if (port_count > 1) {
			u32temp = nes_read_indexed(nesdev, 0x000023f8);
			u32temp &= 0x7fffffff;
			u32temp |= 0x7fff0010;
			nes_write_indexed(nesdev, 0x000023f8, u32temp);
		}
	}
}