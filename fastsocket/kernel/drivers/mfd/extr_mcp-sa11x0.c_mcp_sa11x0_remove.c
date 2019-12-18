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
struct platform_device {int dummy; } ;
struct mcp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mcp_host_unregister (struct mcp*) ; 
 struct mcp* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_mem_region (int,int) ; 

__attribute__((used)) static int mcp_sa11x0_remove(struct platform_device *dev)
{
	struct mcp *mcp = platform_get_drvdata(dev);

	platform_set_drvdata(dev, NULL);
	mcp_host_unregister(mcp);
	release_mem_region(0x80060000, 0x60);

	return 0;
}