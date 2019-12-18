#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_12__ {unsigned long txbytesunicast; unsigned long rxbytesunicast; } ;
struct r8192_priv {int bis_cur_rdlstate; int bcurrent_turbo_EDCA; TYPE_5__ stats; TYPE_4__* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_qos_parameters {int* aifs; scalar_t__* cw_min; scalar_t__* cw_max; scalar_t__* tx_op_limit; } ;
struct TYPE_10__ {scalar_t__ ACM; } ;
struct TYPE_14__ {TYPE_3__ f; } ;
struct TYPE_13__ {int IOTAction; size_t IOTPeer; } ;
struct TYPE_8__ {struct ieee80211_qos_parameters parameters; } ;
struct TYPE_9__ {TYPE_1__ qos_data; } ;
struct TYPE_11__ {scalar_t__ state; int bis_any_nonbepkts; int mode; TYPE_2__ current_network; TYPE_6__* pHTInfo; } ;
typedef  TYPE_6__* PRT_HIGH_THROUGHPUT ;
typedef  TYPE_7__* PACI_AIFSN ;

/* Variables and functions */
 int AC_PARAM_AIFS_OFFSET ; 
 int AC_PARAM_ECW_MAX_OFFSET ; 
 int AC_PARAM_ECW_MIN_OFFSET ; 
 int AC_PARAM_TXOP_LIMIT_OFFSET ; 
 int /*<<< orphan*/  AcmHwCtrl ; 
 int AcmHw_BeqEn ; 
 int /*<<< orphan*/  COMP_QOS ; 
 int /*<<< orphan*/  EDCAPARA_BE ; 
 int HT_IOT_ACT_DISABLE_EDCA_TURBO ; 
 scalar_t__ IEEE80211_LINKED ; 
 int IEEE_G ; 
 int IEEE_N_24G ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 int aSifsTime ; 
 int /*<<< orphan*/  dm_init_edca_turbo (struct net_device*) ; 
 int* edca_setting_DL ; 
 int* edca_setting_UL ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dm_check_edca_turbo(
	struct net_device * dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	PRT_HIGH_THROUGHPUT	pHTInfo = priv->ieee80211->pHTInfo;
	//PSTA_QOS			pStaQos = pMgntInfo->pStaQos;

	// Keep past Tx/Rx packet count for RT-to-RT EDCA turbo.
	static unsigned long			lastTxOkCnt = 0;
	static unsigned long			lastRxOkCnt = 0;
	unsigned long				curTxOkCnt = 0;
	unsigned long				curRxOkCnt = 0;

	//
	// Do not be Turbo if it's under WiFi config and Qos Enabled, because the EDCA parameters
	// should follow the settings from QAP. By Bruce, 2007-12-07.
	//
	#if 1
	if(priv->ieee80211->state != IEEE80211_LINKED)
		goto dm_CheckEdcaTurbo_EXIT;
	#endif
	// We do not turn on EDCA turbo mode for some AP that has IOT issue
	if(priv->ieee80211->pHTInfo->IOTAction & HT_IOT_ACT_DISABLE_EDCA_TURBO)
		goto dm_CheckEdcaTurbo_EXIT;

//	printk("========>%s():bis_any_nonbepkts is %d\n",__FUNCTION__,priv->bis_any_nonbepkts);
	// Check the status for current condition.
	if(!priv->ieee80211->bis_any_nonbepkts)
	{
		curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
		curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;
		// For RT-AP, we needs to turn it on when Rx>Tx
		if(curRxOkCnt > 4*curTxOkCnt)
		{
			//printk("%s():curRxOkCnt > 4*curTxOkCnt\n");
			if(!priv->bis_cur_rdlstate || !priv->bcurrent_turbo_EDCA)
			{
				write_nic_dword(dev, EDCAPARA_BE, edca_setting_DL[pHTInfo->IOTPeer]);
				priv->bis_cur_rdlstate = true;
			}
		}
		else
		{

			//printk("%s():curRxOkCnt < 4*curTxOkCnt\n");
			if(priv->bis_cur_rdlstate || !priv->bcurrent_turbo_EDCA)
			{
				write_nic_dword(dev, EDCAPARA_BE, edca_setting_UL[pHTInfo->IOTPeer]);
				priv->bis_cur_rdlstate = false;
			}

		}

		priv->bcurrent_turbo_EDCA = true;
	}
	else
	{
		//
		// Turn Off EDCA turbo here.
		// Restore original EDCA according to the declaration of AP.
		//
		 if(priv->bcurrent_turbo_EDCA)
		{

			{
				u8		u1bAIFS;
				u32		u4bAcParam;
				struct ieee80211_qos_parameters *qos_parameters = &priv->ieee80211->current_network.qos_data.parameters;
				u8 mode = priv->ieee80211->mode;

			// For Each time updating EDCA parameter, reset EDCA turbo mode status.
				dm_init_edca_turbo(dev);
				u1bAIFS = qos_parameters->aifs[0] * ((mode&(IEEE_G|IEEE_N_24G)) ?9:20) + aSifsTime;
				u4bAcParam = ((((u32)(qos_parameters->tx_op_limit[0]))<< AC_PARAM_TXOP_LIMIT_OFFSET)|
					(((u32)(qos_parameters->cw_max[0]))<< AC_PARAM_ECW_MAX_OFFSET)|
					(((u32)(qos_parameters->cw_min[0]))<< AC_PARAM_ECW_MIN_OFFSET)|
					((u32)u1bAIFS << AC_PARAM_AIFS_OFFSET));
				printk("===>u4bAcParam:%x, ", u4bAcParam);
			//write_nic_dword(dev, WDCAPARA_ADD[i], u4bAcParam);
				write_nic_dword(dev, EDCAPARA_BE,  u4bAcParam);

			// Check ACM bit.
			// If it is set, immediately set ACM control bit to downgrading AC for passing WMM testplan. Annie, 2005-12-13.
				{
			// TODO:  Modified this part and try to set acm control in only 1 IO processing!!

					PACI_AIFSN	pAciAifsn = (PACI_AIFSN)&(qos_parameters->aifs[0]);
					u8		AcmCtrl = read_nic_byte( dev, AcmHwCtrl );
					if( pAciAifsn->f.ACM )
					{ // ACM bit is 1.
						AcmCtrl |= AcmHw_BeqEn;
					}
					else
					{ // ACM bit is 0.
						AcmCtrl &= (~AcmHw_BeqEn);
					}

					RT_TRACE( COMP_QOS,"SetHwReg8190pci(): [HW_VAR_ACM_CTRL] Write 0x%X\n", AcmCtrl ) ;
					write_nic_byte(dev, AcmHwCtrl, AcmCtrl );
				}
			}
			priv->bcurrent_turbo_EDCA = false;
		}
	}


dm_CheckEdcaTurbo_EXIT:
	// Set variables for next time.
	priv->ieee80211->bis_any_nonbepkts = false;
	lastTxOkCnt = priv->stats.txbytesunicast;
	lastRxOkCnt = priv->stats.rxbytesunicast;
}