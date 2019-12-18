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
struct ps3_vuart_port_priv {int dummy; } ;
struct ps3_system_bus_device {scalar_t__ driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static struct ps3_vuart_port_priv *to_port_priv(
	struct ps3_system_bus_device *dev)
{
	BUG_ON(!dev);
	BUG_ON(!dev->driver_priv);
	return (struct ps3_vuart_port_priv *)dev->driver_priv;
}