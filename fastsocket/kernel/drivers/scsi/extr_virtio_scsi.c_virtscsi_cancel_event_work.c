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
struct virtio_scsi {TYPE_1__* event_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int VIRTIO_SCSI_EVENT_LEN ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtscsi_cancel_event_work(struct virtio_scsi *vscsi)
{
	int i;

	for (i = 0; i < VIRTIO_SCSI_EVENT_LEN; i++)
		cancel_work_sync(&vscsi->event_list[i].work);
}