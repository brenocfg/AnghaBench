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
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_local_stock ; 
 int /*<<< orphan*/  memcg_drain_count ; 
 int /*<<< orphan*/  schedule_on_each_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drain_all_stock_sync(void)
{
	/* called when force_empty is called */
	atomic_inc(&memcg_drain_count);
	schedule_on_each_cpu(drain_local_stock);
	atomic_dec(&memcg_drain_count);
}