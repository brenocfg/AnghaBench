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
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct r8192_priv {TYPE_2__ watch_dog_timer; TYPE_1__* ops; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* rtl819x_read_eeprom_info ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dump_eprom (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  init_hal_dm (struct net_device*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  rtl8192_get_channel_map (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_get_eeprom_size (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_init_priv_lock (struct r8192_priv*) ; 
 int /*<<< orphan*/  rtl8192_init_priv_task (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_init_priv_variable (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  watch_dog_timer_callback ; 

short rtl8192_init(struct net_device *dev)
{

	struct r8192_priv *priv = ieee80211_priv(dev);

	rtl8192_init_priv_variable(dev);
	rtl8192_init_priv_lock(priv);
	rtl8192_init_priv_task(dev);
	rtl8192_get_eeprom_size(dev);
	priv->ops->rtl819x_read_eeprom_info(dev);
	rtl8192_get_channel_map(dev);
	init_hal_dm(dev);
	init_timer(&priv->watch_dog_timer);
	priv->watch_dog_timer.data = (unsigned long)dev;
	priv->watch_dog_timer.function = watch_dog_timer_callback;

	//rtl8192_adapter_start(dev);
#ifdef DEBUG_EPROM
	dump_eprom(dev);
#endif
	return 0;
}