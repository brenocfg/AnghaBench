#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct r8192_priv {scalar_t__ RegChannelPlan; void* EepromOrEfuse; void* AutoloadFailFlag; scalar_t__ card_8192_version; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ VERSION_8192S ;
struct TYPE_8__ {int EEPROMChannelPlan; } ;
struct TYPE_7__ {int ChannelPlan; scalar_t__ RegChannelPlan; void* bChnlPlanFromHW; } ;
struct TYPE_6__ {void* bEnabled; } ;
typedef  int RT_CHANNEL_DOMAIN ;
typedef  TYPE_1__* PRT_DOT11D_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  Adapter ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int CmdEEPROM_En ; 
 int CmdEERPOMSEL ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int EEPROM_CHANNEL_PLAN_BY_HW_MASK ; 
 int /*<<< orphan*/  EFUSE_ShadowMapUpdate (struct net_device*) ; 
 int /*<<< orphan*/  EPROM_CMD ; 
 void* FALSE ; 
 TYPE_1__* GET_DOT11D_INFO (TYPE_2__*) ; 
 int HalMapChannelPlan8192S (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PMC_FSM ; 
#define  RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN 128 
 scalar_t__ RT_CHANNEL_DOMAIN_MAX ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 void* TRUE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 TYPE_3__* pHalData ; 
 TYPE_2__* pMgntInfo ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int read_nic_dword (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192SU_ConfigAdapterInfo8192SForAutoLoadFail (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192SU_ReadAdapterInfo8192SUsb (struct net_device*) ; 

__attribute__((used)) static void rtl8192SU_read_eeprom_info(struct net_device *dev)
{
	struct r8192_priv 	*priv = ieee80211_priv(dev);
	u8			tmpU1b;

	RT_TRACE(COMP_INIT, "====> ReadAdapterInfo8192SUsb\n");

	// Retrieve Chip version.
	priv->card_8192_version = (VERSION_8192S)((read_nic_dword(dev, PMC_FSM)>>16)&0xF);
	RT_TRACE(COMP_INIT, "Chip Version ID: 0x%2x\n", priv->card_8192_version);

	tmpU1b = read_nic_byte(dev, EPROM_CMD);//CR9346

	// To check system boot selection.
	if (tmpU1b & CmdEERPOMSEL)
	{
		RT_TRACE(COMP_INIT, "Boot from EEPROM\n");
		priv->EepromOrEfuse = TRUE;
	}
	else
	{
		RT_TRACE(COMP_INIT, "Boot from EFUSE\n");
		priv->EepromOrEfuse = FALSE;
	}

	// To check autoload success or not.
	if (tmpU1b & CmdEEPROM_En)
	{
		RT_TRACE(COMP_INIT, "Autoload OK!!\n");
		priv->AutoloadFailFlag=FALSE;
		rtl8192SU_ReadAdapterInfo8192SUsb(dev);//eeprom or e-fuse
	}
	else
	{ // Auto load fail.
		RT_TRACE(COMP_INIT, "AutoLoad Fail reported from CR9346!!\n");
		priv->AutoloadFailFlag=TRUE;
		rtl8192SU_ConfigAdapterInfo8192SForAutoLoadFail(dev);

		//if (IS_BOOT_FROM_EFUSE(Adapter))
		if(!priv->EepromOrEfuse)
		{
			RT_TRACE(COMP_INIT, "Update shadow map for EFuse future use!!\n");
			EFUSE_ShadowMapUpdate(dev);
		}
	}
#ifdef TO_DO_LIST
	if((priv->RegChannelPlan >= RT_CHANNEL_DOMAIN_MAX) || (pHalData->EEPROMChannelPlan & EEPROM_CHANNEL_PLAN_BY_HW_MASK))
	{
		pMgntInfo->ChannelPlan = HalMapChannelPlan8192S(Adapter, (pHalData->EEPROMChannelPlan & (~(EEPROM_CHANNEL_PLAN_BY_HW_MASK))));
		pMgntInfo->bChnlPlanFromHW = (pHalData->EEPROMChannelPlan & EEPROM_CHANNEL_PLAN_BY_HW_MASK) ? TRUE : FALSE; // User cannot change  channel plan.
	}
	else
	{
		pMgntInfo->ChannelPlan = (RT_CHANNEL_DOMAIN)pMgntInfo->RegChannelPlan;
	}

	switch(pMgntInfo->ChannelPlan)
	{
		case RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN:
		{
			PRT_DOT11D_INFO	pDot11dInfo = GET_DOT11D_INFO(pMgntInfo);

			pDot11dInfo->bEnabled = TRUE;
		}
		RT_TRACE(COMP_INIT, DBG_LOUD, ("ReadAdapterInfo8187(): Enable dot11d when RT_CHANNEL_DOMAIN_GLOBAL_DOAMIN!\n"));
		break;
	}

	RT_TRACE(COMP_INIT, DBG_LOUD, ("RegChannelPlan(%d) EEPROMChannelPlan(%d)", pMgntInfo->RegChannelPlan, pHalData->EEPROMChannelPlan));
	RT_TRACE(COMP_INIT, DBG_LOUD, ("ChannelPlan = %d\n" , pMgntInfo->ChannelPlan));

	RT_TRACE(COMP_INIT, DBG_LOUD, ("<==== ReadAdapterInfo8192S\n"));
#endif

	RT_TRACE(COMP_INIT, "<==== ReadAdapterInfo8192SUsb\n");

	//return RT_STATUS_SUCCESS;
}