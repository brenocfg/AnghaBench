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
struct mcp_driver {int (* probe ) (struct mcp*) ;} ;
struct mcp {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int stub1 (struct mcp*) ; 
 struct mcp* to_mcp (struct device*) ; 
 struct mcp_driver* to_mcp_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp_bus_probe(struct device *dev)
{
	struct mcp *mcp = to_mcp(dev);
	struct mcp_driver *drv = to_mcp_driver(dev->driver);

	return drv->probe(mcp);
}