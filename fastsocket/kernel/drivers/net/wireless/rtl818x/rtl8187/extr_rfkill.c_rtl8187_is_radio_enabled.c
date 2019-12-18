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
typedef  int u8 ;
struct rtl8187_priv {int rfkill_mask; TYPE_1__* map; } ;
struct TYPE_2__ {int /*<<< orphan*/  GPIO1; int /*<<< orphan*/  GPIO0; } ;

/* Variables and functions */
 int rtl818x_ioread8 (struct rtl8187_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl818x_iowrite8 (struct rtl8187_priv*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool rtl8187_is_radio_enabled(struct rtl8187_priv *priv)
{
	u8 gpio;

	gpio = rtl818x_ioread8(priv, &priv->map->GPIO0);
	rtl818x_iowrite8(priv, &priv->map->GPIO0, gpio & ~priv->rfkill_mask);
	gpio = rtl818x_ioread8(priv, &priv->map->GPIO1);

	return gpio & priv->rfkill_mask;
}