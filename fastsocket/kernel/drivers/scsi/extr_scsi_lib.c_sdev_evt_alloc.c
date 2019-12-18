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
struct scsi_event {int evt_type; int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum scsi_device_event { ____Placeholder_scsi_device_event } scsi_device_event ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  SDEV_EVT_MEDIA_CHANGE 128 
 struct scsi_event* kzalloc (int,int /*<<< orphan*/ ) ; 

struct scsi_event *sdev_evt_alloc(enum scsi_device_event evt_type,
				  gfp_t gfpflags)
{
	struct scsi_event *evt = kzalloc(sizeof(struct scsi_event), gfpflags);
	if (!evt)
		return NULL;

	evt->evt_type = evt_type;
	INIT_LIST_HEAD(&evt->node);

	/* evt_type-specific initialization, if any */
	switch (evt_type) {
	case SDEV_EVT_MEDIA_CHANGE:
	default:
		/* do nothing */
		break;
	}

	return evt;
}