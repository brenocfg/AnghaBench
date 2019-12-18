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
struct inet6_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipv6_mc_up (struct inet6_dev*) ; 

void ipv6_mc_remap(struct inet6_dev *idev)
{
	ipv6_mc_up(idev);
}