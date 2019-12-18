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
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {int soft_rx_crc; int mode; int nar; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM8211_IDLE () ; 
 int ADM8211_NAR_EA ; 
 int ADM8211_NAR_PR ; 
 int ADM8211_NAR_SR ; 
 int ADM8211_NAR_ST ; 
 int /*<<< orphan*/  ADM8211_RESTORE () ; 
 int /*<<< orphan*/  ADM8211_REV_BA ; 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_MONITOR 129 
#define  NL80211_IFTYPE_STATION 128 

__attribute__((used)) static void adm8211_update_mode(struct ieee80211_hw *dev)
{
	struct adm8211_priv *priv = dev->priv;

	ADM8211_IDLE();

	priv->soft_rx_crc = 0;
	switch (priv->mode) {
	case NL80211_IFTYPE_STATION:
		priv->nar &= ~(ADM8211_NAR_PR | ADM8211_NAR_EA);
		priv->nar |= ADM8211_NAR_ST | ADM8211_NAR_SR;
		break;
	case NL80211_IFTYPE_ADHOC:
		priv->nar &= ~ADM8211_NAR_PR;
		priv->nar |= ADM8211_NAR_EA | ADM8211_NAR_ST | ADM8211_NAR_SR;

		/* don't trust the error bits on rev 0x20 and up in adhoc */
		if (priv->pdev->revision >= ADM8211_REV_BA)
			priv->soft_rx_crc = 1;
		break;
	case NL80211_IFTYPE_MONITOR:
		priv->nar &= ~(ADM8211_NAR_EA | ADM8211_NAR_ST);
		priv->nar |= ADM8211_NAR_PR | ADM8211_NAR_SR;
		break;
	}

	ADM8211_RESTORE();
}