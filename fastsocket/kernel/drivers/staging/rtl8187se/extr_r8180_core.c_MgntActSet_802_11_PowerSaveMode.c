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
struct r8180_priv {TYPE_1__* ieee80211; } ;
struct TYPE_2__ {scalar_t__ iw_mode; int /*<<< orphan*/  ps; } ;
typedef  int /*<<< orphan*/  RT_PS_MODE ;

/* Variables and functions */
 scalar_t__ IW_MODE_ADHOC ; 

bool
MgntActSet_802_11_PowerSaveMode(
	struct r8180_priv *priv,
	RT_PS_MODE		rtPsMode
)
{
	// Currently, we do not change power save mode on IBSS mode.
	if(priv->ieee80211->iw_mode == IW_MODE_ADHOC)
		return false;

	priv->ieee80211->ps = rtPsMode;

	return true;
}