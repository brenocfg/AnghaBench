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
struct virtio_balloon {scalar_t__ need_stats_update; int /*<<< orphan*/  config_change; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  fill_balloon (struct virtio_balloon*,int /*<<< orphan*/ ) ; 
 scalar_t__ freezing (int /*<<< orphan*/ ) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  leak_balloon (struct virtio_balloon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  stats_handle_request (struct virtio_balloon*) ; 
 int /*<<< orphan*/  towards_target (struct virtio_balloon*) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  update_balloon_size (struct virtio_balloon*) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int balloon(void *_vballoon)
{
	struct virtio_balloon *vb = _vballoon;

	set_freezable();
	while (!kthread_should_stop()) {
		s64 diff;

		try_to_freeze();
		wait_event_interruptible(vb->config_change,
					 (diff = towards_target(vb)) != 0
					 || vb->need_stats_update
					 || kthread_should_stop()
					 || freezing(current));
		if (vb->need_stats_update)
			stats_handle_request(vb);
		if (diff > 0)
			fill_balloon(vb, diff);
		else if (diff < 0)
			leak_balloon(vb, -diff);
		update_balloon_size(vb);
	}
	return 0;
}