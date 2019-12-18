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
 int /*<<< orphan*/  ocrdma_inet6addr_notifier ; 
 int /*<<< orphan*/  unregister_inet6addr_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocrdma_unregister_inet6addr_notifier(void)
{
#if defined(CONFIG_IPV6) || defined(CONFIG_IPV6_MODULE)
	unregister_inet6addr_notifier(&ocrdma_inet6addr_notifier);
#endif
}