#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int genl_register_family (TYPE_1__*) ; 
 TYPE_1__ pmcraid_event_family ; 
 int /*<<< orphan*/  pmcraid_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pmcraid_netlink_init(void)
{
	int result;

	result = genl_register_family(&pmcraid_event_family);

	if (result)
		return result;

	pmcraid_info("registered NETLINK GENERIC group: %d\n",
		     pmcraid_event_family.id);

	return result;
}