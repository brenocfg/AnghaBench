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
typedef  int /*<<< orphan*/  vpd ;
typedef  int /*<<< orphan*/  u8 ;
struct vpd_params {int* port_type; int* eth_base; void** xauicfg; int /*<<< orphan*/  sn; void* mem_timing; void* mdc; void* uclk; void* mclk; void* cclk; } ;
struct t3_vpd {int id_tag; int /*<<< orphan*/ * na_data; int /*<<< orphan*/  xaui1cfg_data; int /*<<< orphan*/  xaui0cfg_data; int /*<<< orphan*/ * port1_data; int /*<<< orphan*/ * port0_data; int /*<<< orphan*/  sn_data; int /*<<< orphan*/  mt_data; int /*<<< orphan*/  mdc_data; int /*<<< orphan*/  uclk_data; int /*<<< orphan*/  mclk_data; int /*<<< orphan*/  cclk_data; } ;
struct TYPE_2__ {scalar_t__ rev; } ;
struct adapter {TYPE_1__ params; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  SERNUM_LEN ; 
 int VPD_BASE ; 
 int hex_to_bin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* simple_strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int t3_seeprom_read (struct adapter*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ uses_xaui (struct adapter*) ; 

__attribute__((used)) static int get_vpd_params(struct adapter *adapter, struct vpd_params *p)
{
	int i, addr, ret;
	struct t3_vpd vpd;

	/*
	 * Card information is normally at VPD_BASE but some early cards had
	 * it at 0.
	 */
	ret = t3_seeprom_read(adapter, VPD_BASE, (__le32 *)&vpd);
	if (ret)
		return ret;
	addr = vpd.id_tag == 0x82 ? VPD_BASE : 0;

	for (i = 0; i < sizeof(vpd); i += 4) {
		ret = t3_seeprom_read(adapter, addr + i,
				      (__le32 *)((u8 *)&vpd + i));
		if (ret)
			return ret;
	}

	p->cclk = simple_strtoul(vpd.cclk_data, NULL, 10);
	p->mclk = simple_strtoul(vpd.mclk_data, NULL, 10);
	p->uclk = simple_strtoul(vpd.uclk_data, NULL, 10);
	p->mdc = simple_strtoul(vpd.mdc_data, NULL, 10);
	p->mem_timing = simple_strtoul(vpd.mt_data, NULL, 10);
	memcpy(p->sn, vpd.sn_data, SERNUM_LEN);

	/* Old eeproms didn't have port information */
	if (adapter->params.rev == 0 && !vpd.port0_data[0]) {
		p->port_type[0] = uses_xaui(adapter) ? 1 : 2;
		p->port_type[1] = uses_xaui(adapter) ? 6 : 2;
	} else {
		p->port_type[0] = hex_to_bin(vpd.port0_data[0]);
		p->port_type[1] = hex_to_bin(vpd.port1_data[0]);
		p->xauicfg[0] = simple_strtoul(vpd.xaui0cfg_data, NULL, 16);
		p->xauicfg[1] = simple_strtoul(vpd.xaui1cfg_data, NULL, 16);
	}

	for (i = 0; i < 6; i++)
		p->eth_base[i] = hex_to_bin(vpd.na_data[2 * i]) * 16 +
				 hex_to_bin(vpd.na_data[2 * i + 1]);
	return 0;
}