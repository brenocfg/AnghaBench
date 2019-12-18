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
struct scsi_device {int /*<<< orphan*/  model; int /*<<< orphan*/  vendor; } ;
struct TYPE_2__ {scalar_t__ model; scalar_t__ vendor; } ;

/* Variables and functions */
 TYPE_1__* clariion_dev_list ; 
 scalar_t__ scsi_device_tpgs (struct scsi_device*) ; 
 int /*<<< orphan*/  strlen (scalar_t__) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool clariion_match(struct scsi_device *sdev)
{
	int i;

	if (scsi_device_tpgs(sdev))
		return false;

	for (i = 0; clariion_dev_list[i].vendor; i++) {
		if (!strncmp(sdev->vendor, clariion_dev_list[i].vendor,
			strlen(clariion_dev_list[i].vendor)) &&
		    !strncmp(sdev->model, clariion_dev_list[i].model,
			strlen(clariion_dev_list[i].model))) {
			return true;
		}
	}
	return false;
}