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
struct mcp_driver {int (* suspend ) (struct mcp*,int /*<<< orphan*/ ) ;} ;
struct mcp {int dummy; } ;
struct device {scalar_t__ driver; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int stub1 (struct mcp*,int /*<<< orphan*/ ) ; 
 struct mcp* to_mcp (struct device*) ; 
 struct mcp_driver* to_mcp_driver (scalar_t__) ; 

__attribute__((used)) static int mcp_bus_suspend(struct device *dev, pm_message_t state)
{
	struct mcp *mcp = to_mcp(dev);
	int ret = 0;

	if (dev->driver) {
		struct mcp_driver *drv = to_mcp_driver(dev->driver);

		ret = drv->suspend(mcp, state);
	}
	return ret;
}