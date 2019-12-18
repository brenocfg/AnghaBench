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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  rnd ;

/* Variables and functions */
 int /*<<< orphan*/  get_random_bytes (scalar_t__*,int) ; 
 scalar_t__ inet_ehash_secret ; 
 int /*<<< orphan*/  inetsw_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void build_ehash_secret(void)
{
	u32 rnd;
	do {
		get_random_bytes(&rnd, sizeof(rnd));
	} while (rnd == 0);
	spin_lock_bh(&inetsw_lock);
	if (!inet_ehash_secret)
		inet_ehash_secret = rnd;
	spin_unlock_bh(&inetsw_lock);
}