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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PLANETCORE_KEY_CRYSTAL_HZ ; 
 int /*<<< orphan*/  PLANETCORE_KEY_KB_NVRAM ; 
 int /*<<< orphan*/  dt_fixup_memory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* finddevice (char*) ; 
 int /*<<< orphan*/  getprop (void*,char*,int*,int) ; 
 int /*<<< orphan*/  ibm405gp_fixup_clocks (int,int) ; 
 int /*<<< orphan*/  ibm4xx_fixup_ebc_ranges (char*) ; 
 int /*<<< orphan*/  ibm4xx_quiesce_eth (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_size ; 
 int /*<<< orphan*/  planetcore_get_decimal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  planetcore_set_mac_addrs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  setprop (void*,char*,int*,int) ; 
 int /*<<< orphan*/  table ; 

__attribute__((used)) static void platform_fixups(void)
{
	u64 val;
	void *nvrtc;

	dt_fixup_memory(0, mem_size);
	planetcore_set_mac_addrs(table);

	if (!planetcore_get_decimal(table, PLANETCORE_KEY_CRYSTAL_HZ, &val)) {
		printf("No PlanetCore crystal frequency key.\r\n");
		return;
	}
	ibm405gp_fixup_clocks(val, 0xa8c000);
	ibm4xx_quiesce_eth((u32 *)0xef600800, NULL);
	ibm4xx_fixup_ebc_ranges("/plb/ebc");

	if (!planetcore_get_decimal(table, PLANETCORE_KEY_KB_NVRAM, &val)) {
		printf("No PlanetCore NVRAM size key.\r\n");
		return;
	}
	nvrtc = finddevice("/plb/ebc/nvrtc@4,200000");
	if (nvrtc != NULL) {
		u32 reg[3] = { 4, 0x200000, 0};
		getprop(nvrtc, "reg", reg, 3);
		reg[2] = (val << 10) & 0xffffffff;
		setprop(nvrtc, "reg", reg, 3);
	}
}