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
struct Scsi_Host {int /*<<< orphan*/  shost_gendev; TYPE_1__* hostt; int /*<<< orphan*/  shost_dev; } ;
struct TYPE_2__ {scalar_t__* shost_attrs; } ;

/* Variables and functions */
 int device_create_file (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  transport_configure_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_register_device (int /*<<< orphan*/ *) ; 

int scsi_sysfs_add_host(struct Scsi_Host *shost)
{
	int error, i;

	/* add host specific attributes */
	if (shost->hostt->shost_attrs) {
		for (i = 0; shost->hostt->shost_attrs[i]; i++) {
			error = device_create_file(&shost->shost_dev,
					shost->hostt->shost_attrs[i]);
			if (error)
				return error;
		}
	}

	transport_register_device(&shost->shost_gendev);
	transport_configure_device(&shost->shost_gendev);
	return 0;
}