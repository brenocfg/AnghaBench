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
struct nlm_block {int b_granted; scalar_t__ b_fl; int /*<<< orphan*/  b_flags; } ;
struct file_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_GOT_CALLBACK ; 
 int /*<<< orphan*/  B_TIMED_OUT ; 
 int /*<<< orphan*/  __locks_copy_lock (scalar_t__,struct file_lock*) ; 

__attribute__((used)) static void
nlmsvc_update_deferred_block(struct nlm_block *block, struct file_lock *conf,
			     int result)
{
	block->b_flags |= B_GOT_CALLBACK;
	if (result == 0)
		block->b_granted = 1;
	else
		block->b_flags |= B_TIMED_OUT;
	if (conf) {
		if (block->b_fl)
			__locks_copy_lock(block->b_fl, conf);
	}
}