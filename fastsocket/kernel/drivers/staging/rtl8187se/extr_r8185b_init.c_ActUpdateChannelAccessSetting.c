#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_21__ ;
typedef  struct TYPE_35__   TYPE_20__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_19__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct r8180_priv {struct ieee80211_device* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_40__ {int Turbo_Enable; } ;
struct ieee80211_device {scalar_t__ iw_mode; TYPE_5__ current_network; } ;
typedef  int /*<<< orphan*/  pu1Byte ;
typedef  scalar_t__ WIRELESS_MODE ;
struct TYPE_44__ {size_t ACI; int AIFSN; } ;
struct TYPE_41__ {int AIFSN; int ACI; scalar_t__ ACM; } ;
struct TYPE_42__ {TYPE_6__ f; } ;
struct TYPE_38__ {int ECWmin; int ECWmax; } ;
struct TYPE_39__ {TYPE_3__ f; } ;
struct TYPE_43__ {int TXOPLimit; TYPE_7__ AciAifsn; TYPE_4__ Ecw; } ;
struct TYPE_37__ {int /*<<< orphan*/ * AcParam; } ;
struct TYPE_36__ {int AcmControl; } ;
struct TYPE_35__ {scalar_t__ CurrentQosMode; scalar_t__ QBssWirelessMode; TYPE_2__ WMMParamEle; } ;
struct TYPE_34__ {int /*<<< orphan*/  (* SetHwRegHandler ) (TYPE_19__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_33__ {TYPE_1__ HalFunc; } ;
struct TYPE_32__ {TYPE_8__ f; scalar_t__ longData; } ;
struct TYPE_28__ {size_t ACI; scalar_t__ ACM; } ;
struct TYPE_31__ {TYPE_14__ f; } ;
struct TYPE_26__ {TYPE_9__ f; } ;
struct TYPE_24__ {scalar_t__ ECWmin; scalar_t__ ECWmax; } ;
struct TYPE_25__ {TYPE_10__ f; } ;
struct TYPE_27__ {TYPE_12__ AciAifsn; TYPE_11__ Ecw; scalar_t__ TXOPLimit; } ;
struct TYPE_30__ {TYPE_13__ f; } ;
struct TYPE_29__ {int SIFS_Timer; int DIFS_Timer; int SlotTimeTimer; int EIFS_Timer; int CWminIndex; int CWmaxIndex; } ;
typedef  TYPE_15__* PCHANNEL_ACCESS_SETTING ;
typedef  TYPE_16__* PAC_PARAM ;
typedef  TYPE_17__* PACI_AIFSN ;
typedef  TYPE_18__ AC_PARAM ;
typedef  size_t AC_CODING ;

/* Variables and functions */
#define  AC0_BE 131 
#define  AC1_BK 130 
#define  AC2_VI 129 
#define  AC3_VO 128 
 int /*<<< orphan*/  ACM_CONTROL ; 
 int ACM_HW_EN ; 
 size_t AC_MAX ; 
 int AC_PARAM_AIFS_OFFSET ; 
 int AC_PARAM_ECW_MAX_OFFSET ; 
 int AC_PARAM_ECW_MIN_OFFSET ; 
 int AC_PARAM_TXOP_LIMIT_OFFSET ; 
 int /*<<< orphan*/  AckTimeOutReg ; 
 TYPE_19__* Adapter ; 
 int BEQ_ACM_CTL ; 
 int BEQ_ACM_EN ; 
 int /*<<< orphan*/  DMESGW (char*,size_t) ; 
 int /*<<< orphan*/  EIFS ; 
 int /*<<< orphan*/  HW_VAR_AC_PARAM ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ QOS_DISABLE ; 
 int /*<<< orphan*/  SIFS ; 
 int /*<<< orphan*/  SLOT ; 
 int VIQ_ACM_CTL ; 
 int VIQ_ACM_EN ; 
 int VOQ_ACM_CTL ; 
 int VOQ_ACM_EN ; 
 int aSifsTime ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 TYPE_21__* pHalData ; 
 TYPE_20__* pStaQos ; 
 int /*<<< orphan*/  stub1 (TYPE_19__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void
ActUpdateChannelAccessSetting(
	struct net_device *dev,
	WIRELESS_MODE			WirelessMode,
	PCHANNEL_ACCESS_SETTING	ChnlAccessSetting
	)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	struct ieee80211_device *ieee = priv->ieee80211;
	AC_CODING	eACI;
	AC_PARAM	AcParam;
	//PSTA_QOS	pStaQos = Adapter->MgntInfo.pStaQos;
	u8	bFollowLegacySetting = 0;
	u8   u1bAIFS;

	//
	// <RJ_TODO_8185B>
	// TODO: We still don't know how to set up these registers, just follow WMAC to
	// verify 8185B FPAG.
	//
	// <RJ_TODO_8185B>
	// Jong said CWmin/CWmax register are not functional in 8185B,
	// so we shall fill channel access realted register into AC parameter registers,
	// even in nQBss.
	//
	ChnlAccessSetting->SIFS_Timer = 0x22; // Suggested by Jong, 2005.12.08.
	ChnlAccessSetting->DIFS_Timer = 0x1C; // 2006.06.02, by rcnjko.
	ChnlAccessSetting->SlotTimeTimer = 9; // 2006.06.02, by rcnjko.
	ChnlAccessSetting->EIFS_Timer = 0x5B; // Suggested by wcchu, it is the default value of EIFS register, 2005.12.08.
	ChnlAccessSetting->CWminIndex = 3; // 2006.06.02, by rcnjko.
	ChnlAccessSetting->CWmaxIndex = 7; // 2006.06.02, by rcnjko.

	write_nic_byte(dev, SIFS, ChnlAccessSetting->SIFS_Timer);
	//Adapter->HalFunc.SetHwRegHandler( Adapter, HW_VAR_SLOT_TIME, &ChnlAccessSetting->SlotTimeTimer );	// Rewrited from directly use PlatformEFIOWrite1Byte(), by Annie, 2006-03-29.
	write_nic_byte(dev, SLOT, ChnlAccessSetting->SlotTimeTimer);	// Rewrited from directly use PlatformEFIOWrite1Byte(), by Annie, 2006-03-29.

	u1bAIFS = aSifsTime + (2 * ChnlAccessSetting->SlotTimeTimer );

	//write_nic_byte(dev, AC_VO_PARAM, u1bAIFS);
	//write_nic_byte(dev, AC_VI_PARAM, u1bAIFS);
	//write_nic_byte(dev, AC_BE_PARAM, u1bAIFS);
	//write_nic_byte(dev, AC_BK_PARAM, u1bAIFS);

	write_nic_byte(dev, EIFS, ChnlAccessSetting->EIFS_Timer);

	write_nic_byte(dev, AckTimeOutReg, 0x5B); // <RJ_EXPR_QOS> Suggested by wcchu, it is the default value of EIFS register, 2005.12.08.

#ifdef TODO
	// <RJ_TODO_NOW_8185B> Update ECWmin/ECWmax, AIFS, TXOP Limit of each AC to the value defined by SPEC.
	if( pStaQos->CurrentQosMode > QOS_DISABLE )
	{ // QoS mode.
		if(pStaQos->QBssWirelessMode == WirelessMode)
		{
			// Follow AC Parameters of the QBSS.
			for(eACI = 0; eACI < AC_MAX; eACI++)
			{
				Adapter->HalFunc.SetHwRegHandler(Adapter, HW_VAR_AC_PARAM, (pu1Byte)(&(pStaQos->WMMParamEle.AcParam[eACI])) );
			}
		}
		else
		{
			// Follow Default WMM AC Parameters.
			bFollowLegacySetting = 1;
		}
	}
	else
#endif
	{ // Legacy 802.11.
		bFollowLegacySetting = 1;

	}

	// this setting is copied from rtl8187B.  xiong-2006-11-13
	if(bFollowLegacySetting)
	{


		//
		// Follow 802.11 seeting to AC parameter, all AC shall use the same parameter.
		// 2005.12.01, by rcnjko.
		//
		AcParam.longData = 0;
		AcParam.f.AciAifsn.f.AIFSN = 2; // Follow 802.11 DIFS.
		AcParam.f.AciAifsn.f.ACM = 0;
		AcParam.f.Ecw.f.ECWmin = ChnlAccessSetting->CWminIndex; // Follow 802.11 CWmin.
		AcParam.f.Ecw.f.ECWmax = ChnlAccessSetting->CWmaxIndex; // Follow 802.11 CWmax.
		AcParam.f.TXOPLimit = 0;

		//lzm reserved 080826
#if 1
		// For turbo mode setting. port from 87B by Isaiah 2008-08-01
		if( ieee->current_network.Turbo_Enable == 1 )
			AcParam.f.TXOPLimit = 0x01FF;
		// For 87SE with Intel 4965  Ad-Hoc mode have poor throughput (19MB)
		if (ieee->iw_mode == IW_MODE_ADHOC)
			AcParam.f.TXOPLimit = 0x0020;
#endif

		for(eACI = 0; eACI < AC_MAX; eACI++)
		{
			AcParam.f.AciAifsn.f.ACI = (u8)eACI;
			{
				PAC_PARAM	pAcParam = (PAC_PARAM)(&AcParam);
				AC_CODING	eACI;
				u8		u1bAIFS;
				u32		u4bAcParam;

				// Retrive paramters to udpate.
				eACI = pAcParam->f.AciAifsn.f.ACI;
				u1bAIFS = pAcParam->f.AciAifsn.f.AIFSN * ChnlAccessSetting->SlotTimeTimer + aSifsTime;
				u4bAcParam = (	(((u32)(pAcParam->f.TXOPLimit)) << AC_PARAM_TXOP_LIMIT_OFFSET)	|
						(((u32)(pAcParam->f.Ecw.f.ECWmax)) << AC_PARAM_ECW_MAX_OFFSET)	|
						(((u32)(pAcParam->f.Ecw.f.ECWmin)) << AC_PARAM_ECW_MIN_OFFSET)	|
						(((u32)u1bAIFS) << AC_PARAM_AIFS_OFFSET));

				switch(eACI)
				{
					case AC1_BK:
						//write_nic_dword(dev, AC_BK_PARAM, u4bAcParam);
						break;

					case AC0_BE:
						//write_nic_dword(dev, AC_BE_PARAM, u4bAcParam);
						break;

					case AC2_VI:
						//write_nic_dword(dev, AC_VI_PARAM, u4bAcParam);
						break;

					case AC3_VO:
						//write_nic_dword(dev, AC_VO_PARAM, u4bAcParam);
						break;

					default:
						DMESGW( "SetHwReg8185(): invalid ACI: %d !\n", eACI);
						break;
				}

				// Cehck ACM bit.
				// If it is set, immediately set ACM control bit to downgrading AC for passing WMM testplan. Annie, 2005-12-13.
				//write_nic_byte(dev, ACM_CONTROL, pAcParam->f.AciAifsn);
				{
					PACI_AIFSN	pAciAifsn = (PACI_AIFSN)(&pAcParam->f.AciAifsn);
					AC_CODING	eACI = pAciAifsn->f.ACI;

					//modified Joseph
					//for 8187B AsynIORead issue
#ifdef TODO
					u8	AcmCtrl = pHalData->AcmControl;
#else
					u8	AcmCtrl = 0;
#endif
					if( pAciAifsn->f.ACM )
					{ // ACM bit is 1.
						switch(eACI)
						{
							case AC0_BE:
								AcmCtrl |= (BEQ_ACM_EN|BEQ_ACM_CTL|ACM_HW_EN);	// or 0x21
								break;

							case AC2_VI:
								AcmCtrl |= (VIQ_ACM_EN|VIQ_ACM_CTL|ACM_HW_EN);	// or 0x42
								break;

							case AC3_VO:
								AcmCtrl |= (VOQ_ACM_EN|VOQ_ACM_CTL|ACM_HW_EN);	// or 0x84
								break;

							default:
								DMESGW("SetHwReg8185(): [HW_VAR_ACM_CTRL] ACM set failed: eACI is %d\n", eACI );
								break;
						}
					}
					else
					{ // ACM bit is 0.
						switch(eACI)
						{
							case AC0_BE:
								AcmCtrl &= ( (~BEQ_ACM_EN) & (~BEQ_ACM_CTL) & (~ACM_HW_EN) );	// and 0xDE
								break;

							case AC2_VI:
								AcmCtrl &= ( (~VIQ_ACM_EN) & (~VIQ_ACM_CTL) & (~ACM_HW_EN) );	// and 0xBD
								break;

							case AC3_VO:
								AcmCtrl &= ( (~VOQ_ACM_EN) & (~VOQ_ACM_CTL) & (~ACM_HW_EN) );	// and 0x7B
								break;

							default:
								break;
						}
					}

					//printk(KERN_WARNING "SetHwReg8185(): [HW_VAR_ACM_CTRL] Write 0x%X\n", AcmCtrl);

#ifdef TO_DO
					pHalData->AcmControl = AcmCtrl;
#endif
					//write_nic_byte(dev, ACM_CONTROL, AcmCtrl);
					write_nic_byte(dev, ACM_CONTROL, 0);
				}
			}
		}


	}
}