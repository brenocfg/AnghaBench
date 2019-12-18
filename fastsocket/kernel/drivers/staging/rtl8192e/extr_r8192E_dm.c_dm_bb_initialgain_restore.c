#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ cca; scalar_t__ xdagccore1; scalar_t__ xcagccore1; scalar_t__ xbagccore1; scalar_t__ xaagccore1; } ;
struct r8192_priv {TYPE_1__ initgain_backup; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ dig_algorithm; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DIG ; 
 scalar_t__ DIG_ALGO_BY_RSSI ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  UFWP ; 
 int bMaskByte1 ; 
 int bMaskByte2 ; 
 TYPE_2__ dm_digtable ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rCCK0_CCA ; 
 int /*<<< orphan*/  rOFDM0_XAAGCCore1 ; 
 int /*<<< orphan*/  rOFDM0_XBAGCCore1 ; 
 int /*<<< orphan*/  rOFDM0_XCAGCCore1 ; 
 int /*<<< orphan*/  rOFDM0_XDAGCCore1 ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void dm_bb_initialgain_restore(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32 bit_mask = 0x7f; //Bit0~ Bit6

	if(dm_digtable.dig_algorithm == DIG_ALGO_BY_RSSI)
		return;

	//Disable Initial Gain
	//PHY_SetBBReg(Adapter, UFWP, bMaskLWord, 0x800);
	rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x8);	// Only clear byte 1 and rewrite.
	rtl8192_setBBreg(dev, rOFDM0_XAAGCCore1, bit_mask, (u32)priv->initgain_backup.xaagccore1);
	rtl8192_setBBreg(dev, rOFDM0_XBAGCCore1, bit_mask, (u32)priv->initgain_backup.xbagccore1);
	rtl8192_setBBreg(dev, rOFDM0_XCAGCCore1, bit_mask, (u32)priv->initgain_backup.xcagccore1);
	rtl8192_setBBreg(dev, rOFDM0_XDAGCCore1, bit_mask, (u32)priv->initgain_backup.xdagccore1);
	bit_mask  = bMaskByte2;
	rtl8192_setBBreg(dev, rCCK0_CCA, bit_mask, (u32)priv->initgain_backup.cca);

	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc50 is %x\n",priv->initgain_backup.xaagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc58 is %x\n",priv->initgain_backup.xbagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc60 is %x\n",priv->initgain_backup.xcagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xc68 is %x\n",priv->initgain_backup.xdagccore1);
	RT_TRACE(COMP_DIG, "dm_BBInitialGainRestore 0xa0a is %x\n",priv->initgain_backup.cca);
	//Enable Initial Gain
	//PHY_SetBBReg(Adapter, UFWP, bMaskLWord, 0x100);
	rtl8192_setBBreg(dev, UFWP, bMaskByte1, 0x1);	// Only clear byte 1 and rewrite.

}