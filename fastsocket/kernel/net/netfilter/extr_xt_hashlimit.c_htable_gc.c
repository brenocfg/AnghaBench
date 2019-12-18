#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;
struct TYPE_3__ {int /*<<< orphan*/  gc_interval; } ;
struct xt_hashlimit_htable {TYPE_2__ timer; TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  htable_selective_cleanup (struct xt_hashlimit_htable*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_gc ; 

__attribute__((used)) static void htable_gc(unsigned long htlong)
{
	struct xt_hashlimit_htable *ht = (struct xt_hashlimit_htable *)htlong;

	htable_selective_cleanup(ht, select_gc);

	/* re-add the timer accordingly */
	ht->timer.expires = jiffies + msecs_to_jiffies(ht->cfg.gc_interval);
	add_timer(&ht->timer);
}