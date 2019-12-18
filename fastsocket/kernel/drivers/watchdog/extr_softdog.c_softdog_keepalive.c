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
 int HZ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int soft_margin ; 
 int /*<<< orphan*/  watchdog_ticktock ; 

__attribute__((used)) static int softdog_keepalive(void)
{
	mod_timer(&watchdog_ticktock, jiffies+(soft_margin*HZ));
	return 0;
}