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
struct virtio_balloon {int dummy; } ;
struct sysinfo {unsigned long freeram; unsigned long totalram; } ;

/* Variables and functions */
 int NR_VM_EVENT_ITEMS ; 
 size_t PGFAULT ; 
 size_t PGMAJFAULT ; 
 size_t PSWPIN ; 
 size_t PSWPOUT ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_MAJFLT ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_MEMFREE ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_MEMTOT ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_MINFLT ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_SWAP_IN ; 
 int /*<<< orphan*/  VIRTIO_BALLOON_S_SWAP_OUT ; 
 int /*<<< orphan*/  all_vm_events (unsigned long*) ; 
 unsigned long pages_to_bytes (unsigned long) ; 
 int /*<<< orphan*/  si_meminfo (struct sysinfo*) ; 
 int /*<<< orphan*/  update_stat (struct virtio_balloon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void update_balloon_stats(struct virtio_balloon *vb)
{
	unsigned long events[NR_VM_EVENT_ITEMS];
	struct sysinfo i;
	int idx = 0;

	all_vm_events(events);
	si_meminfo(&i);

	update_stat(vb, idx++, VIRTIO_BALLOON_S_SWAP_IN,
				pages_to_bytes(events[PSWPIN]));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_SWAP_OUT,
				pages_to_bytes(events[PSWPOUT]));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MAJFLT, events[PGMAJFAULT]);
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MINFLT, events[PGFAULT]);
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MEMFREE,
				pages_to_bytes(i.freeram));
	update_stat(vb, idx++, VIRTIO_BALLOON_S_MEMTOT,
				pages_to_bytes(i.totalram));
}