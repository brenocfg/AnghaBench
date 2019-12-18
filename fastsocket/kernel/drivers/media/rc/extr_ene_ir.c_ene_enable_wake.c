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
struct ene_device {TYPE_1__* pnp_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENE_FW1 ; 
 int /*<<< orphan*/  ENE_FW1_WAKE ; 
 int /*<<< orphan*/  dbg (char*,char*) ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ene_set_clear_reg_mask (struct ene_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ene_enable_wake(struct ene_device *dev, int enable)
{
	enable = enable && device_may_wakeup(&dev->pnp_dev->dev);
	dbg("wake on IR %s", enable ? "enabled" : "disabled");
	ene_set_clear_reg_mask(dev, ENE_FW1, ENE_FW1_WAKE, enable);
}