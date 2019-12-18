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
struct mcp {int /*<<< orphan*/  attached_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*) ; 
 int device_register (int /*<<< orphan*/ *) ; 

int mcp_host_register(struct mcp *mcp)
{
	dev_set_name(&mcp->attached_device, "mcp0");
	return device_register(&mcp->attached_device);
}