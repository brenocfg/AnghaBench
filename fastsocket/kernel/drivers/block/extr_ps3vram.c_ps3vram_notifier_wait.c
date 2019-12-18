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
typedef  int /*<<< orphan*/  u32 ;
struct ps3vram_priv {int /*<<< orphan*/  reports; } ;
struct ps3_system_bus_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  NOTIFIER ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct ps3vram_priv* ps3_system_bus_get_drvdata (struct ps3_system_bus_device*) ; 
 int /*<<< orphan*/ * ps3vram_get_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ps3vram_notifier_wait(struct ps3_system_bus_device *dev,
				 unsigned int timeout_ms)
{
	struct ps3vram_priv *priv = ps3_system_bus_get_drvdata(dev);
	u32 *notify = ps3vram_get_notifier(priv->reports, NOTIFIER);
	unsigned long timeout = jiffies + msecs_to_jiffies(timeout_ms);

	do {
		if (!notify[3])
			return 0;
		msleep(1);
	} while (time_before(jiffies, timeout));

	return -ETIMEDOUT;
}