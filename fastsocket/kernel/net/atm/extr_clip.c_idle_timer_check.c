#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CLIP_CHECK_INTERVAL ; 
 int HZ ; 
 int /*<<< orphan*/  __neigh_for_each_release (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ clip_tbl ; 
 int /*<<< orphan*/  idle_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  neigh_check_cb ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idle_timer_check(unsigned long dummy)
{
	write_lock(&clip_tbl.lock);
	__neigh_for_each_release(&clip_tbl, neigh_check_cb);
	mod_timer(&idle_timer, jiffies + CLIP_CHECK_INTERVAL * HZ);
	write_unlock(&clip_tbl.lock);
}