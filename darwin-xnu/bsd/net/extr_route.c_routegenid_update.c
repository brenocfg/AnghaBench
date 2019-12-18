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
 int /*<<< orphan*/  routegenid_inet6_update () ; 
 int /*<<< orphan*/  routegenid_inet_update () ; 

void
routegenid_update(void)
{
	routegenid_inet_update();
#if INET6
	routegenid_inet6_update();
#endif /* INET6 */
}