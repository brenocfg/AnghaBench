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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct brcms_phy {TYPE_1__* sh; struct bcma_device* d11core; } ;
struct bcma_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  corerev; int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ D11REV_GE (int /*<<< orphan*/ ,int) ; 
 int DUMMY_PKT_LEN ; 
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ON ; 
 int PHY_TXC_ANT_0 ; 
 int bcma_read16 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write16 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ifsstat ; 
 int /*<<< orphan*/  txe_aux ; 
 int /*<<< orphan*/  txe_ctl ; 
 int /*<<< orphan*/  txe_phyctl ; 
 int /*<<< orphan*/  txe_phyctl1 ; 
 int /*<<< orphan*/  txe_status ; 
 int /*<<< orphan*/  txe_wm_0 ; 
 int /*<<< orphan*/  txe_wm_1 ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wepctl ; 
 int /*<<< orphan*/  wlapi_bmac_write_template_ram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlc_phy_pa_override_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmtsel ; 
 int /*<<< orphan*/  xmttplatetxptr ; 
 int /*<<< orphan*/  xmttxcnt ; 

void wlc_phy_do_dummy_tx(struct brcms_phy *pi, bool ofdm, bool pa_on)
{
#define DUMMY_PKT_LEN   20
	struct bcma_device *core = pi->d11core;
	int i, count;
	u8 ofdmpkt[DUMMY_PKT_LEN] = {
		0xcc, 0x01, 0x02, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
	};
	u8 cckpkt[DUMMY_PKT_LEN] = {
		0x6e, 0x84, 0x0b, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00
	};
	u32 *dummypkt;

	dummypkt = (u32 *) (ofdm ? ofdmpkt : cckpkt);
	wlapi_bmac_write_template_ram(pi->sh->physhim, 0, DUMMY_PKT_LEN,
				      dummypkt);

	bcma_write16(core, D11REGOFFS(xmtsel), 0);

	if (D11REV_GE(pi->sh->corerev, 11))
		bcma_write16(core, D11REGOFFS(wepctl), 0x100);
	else
		bcma_write16(core, D11REGOFFS(wepctl), 0);

	bcma_write16(core, D11REGOFFS(txe_phyctl),
		     (ofdm ? 1 : 0) | PHY_TXC_ANT_0);
	if (ISNPHY(pi) || ISLCNPHY(pi))
		bcma_write16(core, D11REGOFFS(txe_phyctl1), 0x1A02);

	bcma_write16(core, D11REGOFFS(txe_wm_0), 0);
	bcma_write16(core, D11REGOFFS(txe_wm_1), 0);

	bcma_write16(core, D11REGOFFS(xmttplatetxptr), 0);
	bcma_write16(core, D11REGOFFS(xmttxcnt), DUMMY_PKT_LEN);

	bcma_write16(core, D11REGOFFS(xmtsel),
		     ((8 << 8) | (1 << 5) | (1 << 2) | 2));

	bcma_write16(core, D11REGOFFS(txe_ctl), 0);

	if (!pa_on) {
		if (ISNPHY(pi))
			wlc_phy_pa_override_nphy(pi, OFF);
	}

	if (ISNPHY(pi) || ISLCNPHY(pi))
		bcma_write16(core, D11REGOFFS(txe_aux), 0xD0);
	else
		bcma_write16(core, D11REGOFFS(txe_aux), ((1 << 5) | (1 << 4)));

	(void)bcma_read16(core, D11REGOFFS(txe_aux));

	i = 0;
	count = ofdm ? 30 : 250;
	while ((i++ < count)
	       && (bcma_read16(core, D11REGOFFS(txe_status)) & (1 << 7)))
		udelay(10);

	i = 0;

	while ((i++ < 10) &&
	       ((bcma_read16(core, D11REGOFFS(txe_status)) & (1 << 10)) == 0))
		udelay(10);

	i = 0;

	while ((i++ < 10) &&
	       ((bcma_read16(core, D11REGOFFS(ifsstat)) & (1 << 8))))
		udelay(10);

	if (!pa_on) {
		if (ISNPHY(pi))
			wlc_phy_pa_override_nphy(pi, ON);
	}
}