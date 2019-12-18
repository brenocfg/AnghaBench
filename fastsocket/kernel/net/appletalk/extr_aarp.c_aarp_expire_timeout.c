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
 int AARP_HASH_SIZE ; 
 int /*<<< orphan*/  __aarp_expire_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __aarp_kick (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarp_lock ; 
 int /*<<< orphan*/  aarp_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * proxies ; 
 int /*<<< orphan*/ * resolved ; 
 scalar_t__ sysctl_aarp_expiry_time ; 
 scalar_t__ sysctl_aarp_tick_time ; 
 int /*<<< orphan*/ * unresolved ; 
 scalar_t__ unresolved_count ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aarp_expire_timeout(unsigned long unused)
{
	int ct;

	write_lock_bh(&aarp_lock);

	for (ct = 0; ct < AARP_HASH_SIZE; ct++) {
		__aarp_expire_timer(&resolved[ct]);
		__aarp_kick(&unresolved[ct]);
		__aarp_expire_timer(&unresolved[ct]);
		__aarp_expire_timer(&proxies[ct]);
	}

	write_unlock_bh(&aarp_lock);
	mod_timer(&aarp_timer, jiffies +
			       (unresolved_count ? sysctl_aarp_tick_time :
				sysctl_aarp_expiry_time));
}