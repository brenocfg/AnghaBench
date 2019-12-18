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
struct nlm_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nlm_blocked_lock ; 
 int /*<<< orphan*/  nlmsvc_insert_block_locked (struct nlm_block*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nlmsvc_insert_block(struct nlm_block *block, unsigned long when)
{
	spin_lock(&nlm_blocked_lock);
	nlmsvc_insert_block_locked(block, when);
	spin_unlock(&nlm_blocked_lock);
}