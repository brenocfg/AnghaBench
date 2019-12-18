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
typedef  int u32 ;
struct ps3vram_priv {int /*<<< orphan*/  reports; } ;
struct ps3_system_bus_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOTIFIER ; 
 struct ps3vram_priv* ps3_system_bus_get_drvdata (struct ps3_system_bus_device*) ; 
 int* ps3vram_get_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ps3vram_notifier_reset(struct ps3_system_bus_device *dev)
{
	struct ps3vram_priv *priv = ps3_system_bus_get_drvdata(dev);
	u32 *notify = ps3vram_get_notifier(priv->reports, NOTIFIER);
	int i;

	for (i = 0; i < 4; i++)
		notify[i] = 0xffffffff;
}