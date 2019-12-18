#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct wbsoft_priv {int /*<<< orphan*/  sHwData; } ;
struct ieee80211_hw {struct wbsoft_priv* priv; } ;
struct TYPE_3__ {int band; int ChanNo; } ;
typedef  TYPE_1__ ChanInfo ;

/* Variables and functions */
 int /*<<< orphan*/  hal_set_accept_beacon (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hal_set_accept_broadcast (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hal_set_accept_multicast (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hal_set_accept_promiscuous (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hal_set_current_channel (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  hal_set_radio_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int wbsoft_config(struct ieee80211_hw *dev, u32 changed)
{
	struct wbsoft_priv *priv = dev->priv;
	ChanInfo ch;

	printk("wbsoft_config called\n");

	/* Should use channel_num, or something, as that is already pre-translated */
	ch.band = 1;
	ch.ChanNo = 1;

	hal_set_current_channel(&priv->sHwData, ch);
	hal_set_accept_broadcast(&priv->sHwData, 1);
	hal_set_accept_promiscuous(&priv->sHwData, 1);
	hal_set_accept_multicast(&priv->sHwData, 1);
	hal_set_accept_beacon(&priv->sHwData, 1);
	hal_set_radio_mode(&priv->sHwData, 0);

	return 0;
}