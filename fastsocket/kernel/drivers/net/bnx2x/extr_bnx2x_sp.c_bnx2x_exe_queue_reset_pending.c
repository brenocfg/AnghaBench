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
struct bnx2x_exe_queue_obj {int /*<<< orphan*/  lock; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bnx2x_exe_queue_reset_pending (struct bnx2x*,struct bnx2x_exe_queue_obj*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void bnx2x_exe_queue_reset_pending(struct bnx2x *bp,
						 struct bnx2x_exe_queue_obj *o)
{
	spin_lock_bh(&o->lock);

	__bnx2x_exe_queue_reset_pending(bp, o);

	spin_unlock_bh(&o->lock);
}