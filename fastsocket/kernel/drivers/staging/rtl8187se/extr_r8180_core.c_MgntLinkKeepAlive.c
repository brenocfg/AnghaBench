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
struct TYPE_3__ {scalar_t__ LastNumTxUnicast; scalar_t__ LastNumRxUnicast; int IdleCount; } ;
struct r8180_priv {int keepAliveLevel; scalar_t__ NumTxUnicast; TYPE_2__* ieee80211; TYPE_1__ link_detect; } ;
struct TYPE_4__ {scalar_t__ state; scalar_t__ NumRxUnicast; } ;

/* Variables and functions */
 int CHECK_FOR_HANG_PERIOD ; 
 scalar_t__ IEEE80211_LINKED ; 
 int KEEP_ALIVE_INTERVAL ; 
 int /*<<< orphan*/  ieee80211_sta_ps_send_null_frame (TYPE_2__*,int) ; 

__attribute__((used)) static void MgntLinkKeepAlive(struct r8180_priv *priv )
{
	if (priv->keepAliveLevel == 0)
		return;

	if(priv->ieee80211->state == IEEE80211_LINKED)
	{
		//
		// Keep-Alive.
		//

		if ( (priv->keepAliveLevel== 2) ||
			(priv->link_detect.LastNumTxUnicast == priv->NumTxUnicast &&
			priv->link_detect.LastNumRxUnicast == priv->ieee80211->NumRxUnicast )
			)
		{
			priv->link_detect.IdleCount++;

			//
			// Send a Keep-Alive packet packet to AP if we had been idle for a while.
			//
			if(priv->link_detect.IdleCount >= ((KEEP_ALIVE_INTERVAL / CHECK_FOR_HANG_PERIOD)-1) )
			{
				priv->link_detect.IdleCount = 0;
				ieee80211_sta_ps_send_null_frame(priv->ieee80211, false);
			}
		}
		else
		{
			priv->link_detect.IdleCount = 0;
		}
		priv->link_detect.LastNumTxUnicast = priv->NumTxUnicast;
		priv->link_detect.LastNumRxUnicast = priv->ieee80211->NumRxUnicast;
	}
}