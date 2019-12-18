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
 int /*<<< orphan*/  __aarp_expire_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aarp_lock ; 
 int /*<<< orphan*/ * proxies ; 
 int /*<<< orphan*/ * resolved ; 
 int /*<<< orphan*/ * unresolved ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aarp_purge(void)
{
	int ct;

	write_lock_bh(&aarp_lock);
	for (ct = 0; ct < AARP_HASH_SIZE; ct++) {
		__aarp_expire_all(&resolved[ct]);
		__aarp_expire_all(&unresolved[ct]);
		__aarp_expire_all(&proxies[ct]);
	}
	write_unlock_bh(&aarp_lock);
}