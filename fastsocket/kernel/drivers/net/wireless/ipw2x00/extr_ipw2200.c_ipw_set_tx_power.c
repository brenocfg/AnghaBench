#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tx_power ;
struct libipw_geo {int bg_channels; int a_channels; TYPE_2__* a; TYPE_1__* bg; } ;
struct ipw_tx_power {int num_channels; TYPE_3__* channels_tx_power; int /*<<< orphan*/  ieee_mode; } ;
struct ipw_priv {void* tx_power; TYPE_4__* ieee; } ;
typedef  scalar_t__ s8 ;
struct TYPE_8__ {scalar_t__ abg_true; } ;
struct TYPE_7__ {void* tx_power; int /*<<< orphan*/  channel_number; } ;
struct TYPE_6__ {int /*<<< orphan*/  channel; scalar_t__ max_power; } ;
struct TYPE_5__ {int /*<<< orphan*/  channel; scalar_t__ max_power; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IPW_A_MODE ; 
 int /*<<< orphan*/  IPW_B_MODE ; 
 int /*<<< orphan*/  IPW_G_MODE ; 
 scalar_t__ ipw_send_tx_power (struct ipw_priv*,struct ipw_tx_power*) ; 
 struct libipw_geo* libipw_get_geo (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (struct ipw_tx_power*,int /*<<< orphan*/ ,int) ; 
 void* min (scalar_t__,void*) ; 

__attribute__((used)) static int ipw_set_tx_power(struct ipw_priv *priv)
{
	const struct libipw_geo *geo = libipw_get_geo(priv->ieee);
	struct ipw_tx_power tx_power;
	s8 max_power;
	int i;

	memset(&tx_power, 0, sizeof(tx_power));

	/* configure device for 'G' band */
	tx_power.ieee_mode = IPW_G_MODE;
	tx_power.num_channels = geo->bg_channels;
	for (i = 0; i < geo->bg_channels; i++) {
		max_power = geo->bg[i].max_power;
		tx_power.channels_tx_power[i].channel_number =
		    geo->bg[i].channel;
		tx_power.channels_tx_power[i].tx_power = max_power ?
		    min(max_power, priv->tx_power) : priv->tx_power;
	}
	if (ipw_send_tx_power(priv, &tx_power))
		return -EIO;

	/* configure device to also handle 'B' band */
	tx_power.ieee_mode = IPW_B_MODE;
	if (ipw_send_tx_power(priv, &tx_power))
		return -EIO;

	/* configure device to also handle 'A' band */
	if (priv->ieee->abg_true) {
		tx_power.ieee_mode = IPW_A_MODE;
		tx_power.num_channels = geo->a_channels;
		for (i = 0; i < tx_power.num_channels; i++) {
			max_power = geo->a[i].max_power;
			tx_power.channels_tx_power[i].channel_number =
			    geo->a[i].channel;
			tx_power.channels_tx_power[i].tx_power = max_power ?
			    min(max_power, priv->tx_power) : priv->tx_power;
		}
		if (ipw_send_tx_power(priv, &tx_power))
			return -EIO;
	}
	return 0;
}