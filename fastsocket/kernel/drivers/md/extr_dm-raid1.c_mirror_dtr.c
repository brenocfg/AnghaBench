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
struct mirror_set {int /*<<< orphan*/  nr_mirrors; int /*<<< orphan*/  kmirrord_wq; int /*<<< orphan*/  kcopyd_client; int /*<<< orphan*/  timer; } ;
struct dm_target {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_kcopyd_client_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_context (struct mirror_set*,struct dm_target*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mirror_dtr(struct dm_target *ti)
{
	struct mirror_set *ms = (struct mirror_set *) ti->private;

	del_timer_sync(&ms->timer);
	flush_workqueue(ms->kmirrord_wq);
	flush_scheduled_work();
	dm_kcopyd_client_destroy(ms->kcopyd_client);
	destroy_workqueue(ms->kmirrord_wq);
	free_context(ms, ti, ms->nr_mirrors);
}