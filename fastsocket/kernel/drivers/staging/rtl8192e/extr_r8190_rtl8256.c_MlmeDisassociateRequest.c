#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct r8192_priv {int OpMode; TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int* bssid; } ;
struct TYPE_6__ {TYPE_1__ current_network; int /*<<< orphan*/  state; } ;
typedef  int RT_OP_MODE ;

/* Variables and functions */
 scalar_t__ BSSIDR ; 
 int /*<<< orphan*/  IEEE80211_NOLINK ; 
 int /*<<< orphan*/  MSR ; 
 int MSR_LINK_ADHOC ; 
 int MSR_LINK_MANAGED ; 
 int MSR_LINK_MASTER ; 
 int MSR_LINK_NONE ; 
#define  RT_OP_MODE_AP 130 
#define  RT_OP_MODE_IBSS 129 
#define  RT_OP_MODE_INFRASTRUCTURE 128 
 int RT_OP_MODE_NO_LINK ; 
 int /*<<< orphan*/  RemovePeerTS (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  SendDisassociation (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  ieee80211_disassociate (TYPE_2__*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/ * memcpy (int*,int*,int) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
MlmeDisassociateRequest(
	struct net_device* dev,
	u8* 		asSta,
	u8			asRsn
	)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u8 i;

	RemovePeerTS(priv->ieee80211, asSta);

	SendDisassociation( priv->ieee80211, asSta, asRsn );

	if(memcpy(priv->ieee80211->current_network.bssid,asSta,6) == NULL)
	{
		//ShuChen TODO: change media status.
		//ShuChen TODO: What to do when disassociate.
		priv->ieee80211->state = IEEE80211_NOLINK;
		//pMgntInfo->AsocTimestamp = 0;
		for(i=0;i<6;i++)  priv->ieee80211->current_network.bssid[i] = 0x22;
//		pMgntInfo->mBrates.Length = 0;
//		Adapter->HalFunc.SetHwRegHandler( Adapter, HW_VAR_BASIC_RATE, (pu1Byte)(&pMgntInfo->mBrates) );
		priv->OpMode = RT_OP_MODE_NO_LINK;
		{
			RT_OP_MODE	OpMode = priv->OpMode;
			//LED_CTL_MODE	LedAction = LED_CTL_NO_LINK;
			u8 btMsr = read_nic_byte(dev, MSR);

			btMsr &= 0xfc;

			switch(OpMode)
			{
			case RT_OP_MODE_INFRASTRUCTURE:
				btMsr |= MSR_LINK_MANAGED;
				//LedAction = LED_CTL_LINK;
				break;

			case RT_OP_MODE_IBSS:
				btMsr |= MSR_LINK_ADHOC;
				// led link set seperate
				break;

			case RT_OP_MODE_AP:
				btMsr |= MSR_LINK_MASTER;
				//LedAction = LED_CTL_LINK;
				break;

			default:
				btMsr |= MSR_LINK_NONE;
				break;
			}

			write_nic_byte(dev, MSR, btMsr);

			// LED control
			//Adapter->HalFunc.LedControlHandler(Adapter, LedAction);
		}
		ieee80211_disassociate(priv->ieee80211);

		write_nic_word(dev, BSSIDR, ((u16*)priv->ieee80211->current_network.bssid)[0]);
		write_nic_dword(dev, BSSIDR+2, ((u32*)(priv->ieee80211->current_network.bssid+2))[0]);

	}

}