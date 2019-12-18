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
struct scsi_event {int evt_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct scsi_device {TYPE_1__ sdev_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_CHANGE ; 
#define  SDEV_EVT_MEDIA_CHANGE 128 
 int /*<<< orphan*/  kobject_uevent_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static void scsi_evt_emit(struct scsi_device *sdev, struct scsi_event *evt)
{
	int idx = 0;
	char *envp[3];

	switch (evt->evt_type) {
	case SDEV_EVT_MEDIA_CHANGE:
		envp[idx++] = "SDEV_MEDIA_CHANGE=1";
		break;

	default:
		/* do nothing */
		break;
	}

	envp[idx++] = NULL;

	kobject_uevent_env(&sdev->sdev_gendev.kobj, KOBJ_CHANGE, envp);
}