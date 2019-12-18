#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  txfeedbackretry; int /*<<< orphan*/  txretrycount; int /*<<< orphan*/  txerrunicast; int /*<<< orphan*/  txerrbroadcast; int /*<<< orphan*/  txerrmulticast; int /*<<< orphan*/  txerrbytestotal; int /*<<< orphan*/  txerrtotal; int /*<<< orphan*/  txfeedbackfail; int /*<<< orphan*/  txbytesunicast; int /*<<< orphan*/  txunicast; int /*<<< orphan*/  txbytesbroadcast; int /*<<< orphan*/  txbroadcast; int /*<<< orphan*/  txbytesmulticast; int /*<<< orphan*/  txmulticast; int /*<<< orphan*/  txokinperiod; int /*<<< orphan*/  txokbytestotal; int /*<<< orphan*/  txoktotal; int /*<<< orphan*/  txfeedbackok; } ;
struct r8192_priv {TYPE_2__ stats; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  pu1Byte ;
struct TYPE_9__ {scalar_t__ pkt_type; scalar_t__ retry_cnt; scalar_t__ pkt_length; scalar_t__ tok; } ;
typedef  TYPE_3__ cmpk_txfb_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* GetHwRegHandler ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {scalar_t__ bInHctTest; TYPE_1__ HalFunc; } ;
typedef  scalar_t__ RT_RF_POWER_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_RF_STATE ; 
 scalar_t__ PACKET_BROADCAST ; 
 scalar_t__ PACKET_MULTICAST ; 
 scalar_t__ eRfOff ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 TYPE_4__* pAdapter ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	void
cmpk_count_txstatistic(
	struct net_device *dev,
	cmpk_txfb_t	*pstx_fb)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
#ifdef ENABLE_PS
	RT_RF_POWER_STATE	rtState;

	pAdapter->HalFunc.GetHwRegHandler(pAdapter, HW_VAR_RF_STATE, (pu1Byte)(&rtState));

	// When RF is off, we should not count the packet for hw/sw synchronize
	// reason, ie. there may be a duration while sw switch is changed and hw
	// switch is being changed. 2006.12.04, by shien chang.
	if (rtState == eRfOff)
	{
		return;
	}
#endif

#ifdef TODO
	if(pAdapter->bInHctTest)
		return;
#endif
	/* We can not know the packet length and transmit type: broadcast or uni
	   or multicast. So the relative statistics must be collected in tx
	   feedback info. */
	if (pstx_fb->tok)
	{
		priv->stats.txfeedbackok++;
		priv->stats.txoktotal++;
		priv->stats.txokbytestotal += pstx_fb->pkt_length;
		priv->stats.txokinperiod++;

		/* We can not make sure broadcast/multicast or unicast mode. */
		if (pstx_fb->pkt_type == PACKET_MULTICAST)
		{
			priv->stats.txmulticast++;
			priv->stats.txbytesmulticast += pstx_fb->pkt_length;
		}
		else if (pstx_fb->pkt_type == PACKET_BROADCAST)
		{
			priv->stats.txbroadcast++;
			priv->stats.txbytesbroadcast += pstx_fb->pkt_length;
		}
		else
		{
			priv->stats.txunicast++;
			priv->stats.txbytesunicast += pstx_fb->pkt_length;
		}
	}
	else
	{
		priv->stats.txfeedbackfail++;
		priv->stats.txerrtotal++;
		priv->stats.txerrbytestotal += pstx_fb->pkt_length;

		/* We can not make sure broadcast/multicast or unicast mode. */
		if (pstx_fb->pkt_type == PACKET_MULTICAST)
		{
			priv->stats.txerrmulticast++;
		}
		else if (pstx_fb->pkt_type == PACKET_BROADCAST)
		{
			priv->stats.txerrbroadcast++;
		}
		else
		{
			priv->stats.txerrunicast++;
		}
	}

	priv->stats.txretrycount += pstx_fb->retry_cnt;
	priv->stats.txfeedbackretry += pstx_fb->retry_cnt;

}