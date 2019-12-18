#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ipv6; scalar_t__ icmpv6; scalar_t__ icmpv6msg; } ;
struct inet6_dev {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  snmp_mib_free (void**) ; 

__attribute__((used)) static void snmp6_free_dev(struct inet6_dev *idev)
{
	snmp_mib_free((void **)idev->stats.icmpv6msg);
	snmp_mib_free((void **)idev->stats.icmpv6);
	snmp_mib_free((void **)idev->stats.ipv6);
}