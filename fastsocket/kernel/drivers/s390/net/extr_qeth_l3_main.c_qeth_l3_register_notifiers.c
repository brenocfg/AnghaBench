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
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  qeth_l3_ip6_notifier ; 
 int /*<<< orphan*/  qeth_l3_ip_notifier ; 
 int register_inet6addr_notifier (int /*<<< orphan*/ *) ; 
 int register_inetaddr_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_inetaddr_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_l3_register_notifiers(void)
{
	int rc;

	QETH_DBF_TEXT(TRACE, 5, "regnotif");
	rc = register_inetaddr_notifier(&qeth_l3_ip_notifier);
	if (rc)
		return rc;
#ifdef CONFIG_QETH_IPV6
	rc = register_inet6addr_notifier(&qeth_l3_ip6_notifier);
	if (rc) {
		unregister_inetaddr_notifier(&qeth_l3_ip_notifier);
		return rc;
	}
#else
	pr_warning("There is no IPv6 support for the layer 3 discipline\n");
#endif
	return 0;
}