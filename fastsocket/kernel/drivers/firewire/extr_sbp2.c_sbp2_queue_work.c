#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sbp2_logical_unit {TYPE_1__* tgt; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sbp2_target_put (TYPE_1__*) ; 
 int /*<<< orphan*/  sbp2_wq ; 

__attribute__((used)) static void sbp2_queue_work(struct sbp2_logical_unit *lu, unsigned long delay)
{
	kref_get(&lu->tgt->kref);
	if (!queue_delayed_work(sbp2_wq, &lu->work, delay))
		sbp2_target_put(lu->tgt);
}