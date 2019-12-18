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
typedef  size_t u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct mce {int addr; int /*<<< orphan*/  extcpu; } ;
struct cpuinfo_x86 {int x86; } ;
struct amd64_pvt {int /*<<< orphan*/  F1; } ;
struct TYPE_2__ {struct amd64_pvt* pvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRAM_LOCAL_NODE_BASE ; 
 int /*<<< orphan*/  DRAM_LOCAL_NODE_LIM ; 
 int GENMASK (int,int) ; 
 int __fls (size_t) ; 
 int /*<<< orphan*/  amd64_read_pci_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 size_t amd_get_nb_id (int /*<<< orphan*/ ) ; 
 struct cpuinfo_x86 boot_cpu_data ; 
 TYPE_1__** mcis ; 

__attribute__((used)) static u64 get_error_address(struct mce *m)
{
	struct cpuinfo_x86 *c = &boot_cpu_data;
	u64 addr;
	u8 start_bit = 1;
	u8 end_bit   = 47;

	if (c->x86 == 0xf) {
		start_bit = 3;
		end_bit   = 39;
	}

	addr = m->addr & GENMASK(start_bit, end_bit);

	/*
	 * Erratum 637 workaround
	 */
	if (c->x86 == 0x15) {
		struct amd64_pvt *pvt;
		u64 cc6_base, tmp_addr;
		u32 tmp;
		u8 mce_nid, intlv_en;

		if ((addr & GENMASK(24, 47)) >> 24 != 0x00fdf7)
			return addr;

		mce_nid	= amd_get_nb_id(m->extcpu);
		pvt	= mcis[mce_nid]->pvt_info;

		amd64_read_pci_cfg(pvt->F1, DRAM_LOCAL_NODE_LIM, &tmp);
		intlv_en = tmp >> 21 & 0x7;

		/* add [47:27] + 3 trailing bits */
		cc6_base  = (tmp & GENMASK(0, 20)) << 3;

		/* reverse and add DramIntlvEn */
		cc6_base |= intlv_en ^ 0x7;

		/* pin at [47:24] */
		cc6_base <<= 24;

		if (!intlv_en)
			return cc6_base | (addr & GENMASK(0, 23));

		amd64_read_pci_cfg(pvt->F1, DRAM_LOCAL_NODE_BASE, &tmp);

							/* faster log2 */
		tmp_addr  = (addr & GENMASK(12, 23)) << __fls(intlv_en + 1);

		/* OR DramIntlvSel into bits [14:12] */
		tmp_addr |= (tmp & GENMASK(21, 23)) >> 9;

		/* add remaining [11:0] bits from original MC4_ADDR */
		tmp_addr |= addr & GENMASK(0, 11);

		return cc6_base | tmp_addr;
	}

	return addr;
}