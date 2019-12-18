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
typedef  int /*<<< orphan*/  u32 ;
struct route4_head {int /*<<< orphan*/  fastmap; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * qdisc_root_sleeping_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline
void route4_reset_fastmap(struct Qdisc *q, struct route4_head *head, u32 id)
{
	spinlock_t *root_lock = qdisc_root_sleeping_lock(q);

	spin_lock_bh(root_lock);
	memset(head->fastmap, 0, sizeof(head->fastmap));
	spin_unlock_bh(root_lock);
}