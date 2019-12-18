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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  qeth_l3_ip6_notifier ; 
 int /*<<< orphan*/  qeth_l3_ip_notifier ; 
 int /*<<< orphan*/  unregister_inet6addr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_inetaddr_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_l3_unregister_notifiers(void)
{

	QETH_DBF_TEXT(TRACE, 5, "unregnot");
	BUG_ON(unregister_inetaddr_notifier(&qeth_l3_ip_notifier));
#ifdef CONFIG_QETH_IPV6
	BUG_ON(unregister_inet6addr_notifier(&qeth_l3_ip6_notifier));
#endif /* QETH_IPV6 */
}