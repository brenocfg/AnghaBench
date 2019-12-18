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

/* Variables and functions */
 int /*<<< orphan*/  genl_unregister_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmcraid_event_family ; 

__attribute__((used)) static void pmcraid_netlink_release(void)
{
	genl_unregister_family(&pmcraid_event_family);
}