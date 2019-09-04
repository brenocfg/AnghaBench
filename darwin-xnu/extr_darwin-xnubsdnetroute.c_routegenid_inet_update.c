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
 int /*<<< orphan*/  atomic_add_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  route_genid_inet ; 

void
routegenid_inet_update(void)
{
	atomic_add_32(&route_genid_inet, 1);
}