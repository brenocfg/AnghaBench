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
struct TYPE_2__ {scalar_t__ expires; } ;
struct ioc3_private {TYPE_1__ ioc3_timer; int /*<<< orphan*/  mii; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  ioc3_setup_duplex (struct ioc3_private*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ioc3_timer(unsigned long data)
{
	struct ioc3_private *ip = (struct ioc3_private *) data;

	/* Print the link status if it has changed */
	mii_check_media(&ip->mii, 1, 0);
	ioc3_setup_duplex(ip);

	ip->ioc3_timer.expires = jiffies + ((12 * HZ)/10); /* 1.2s */
	add_timer(&ip->ioc3_timer);
}