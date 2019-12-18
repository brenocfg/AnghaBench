#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ps3_vuart_port_priv {int interrupt_mask; } ;
struct ps3_system_bus_device {int dummy; } ;

/* Variables and functions */
 int INTERRUPT_MASK_TX ; 
 int ps3_vuart_set_interrupt_mask (struct ps3_system_bus_device*,int) ; 
 struct ps3_vuart_port_priv* to_port_priv (struct ps3_system_bus_device*) ; 

int ps3_vuart_disable_interrupt_tx(struct ps3_system_bus_device *dev)
{
	struct ps3_vuart_port_priv *priv = to_port_priv(dev);

	return (priv->interrupt_mask & INTERRUPT_MASK_TX)
		? ps3_vuart_set_interrupt_mask(dev, priv->interrupt_mask
		& ~INTERRUPT_MASK_TX) : 0;
}