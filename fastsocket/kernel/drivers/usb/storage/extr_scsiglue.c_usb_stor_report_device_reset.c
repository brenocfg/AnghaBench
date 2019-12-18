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
struct us_data {int fflags; } ;
struct Scsi_Host {int max_id; } ;

/* Variables and functions */
 int US_FL_SCM_MULT_TARG ; 
 int /*<<< orphan*/  scsi_report_device_reset (struct Scsi_Host*,int /*<<< orphan*/ ,int) ; 
 struct Scsi_Host* us_to_host (struct us_data*) ; 

void usb_stor_report_device_reset(struct us_data *us)
{
	int i;
	struct Scsi_Host *host = us_to_host(us);

	scsi_report_device_reset(host, 0, 0);
	if (us->fflags & US_FL_SCM_MULT_TARG) {
		for (i = 1; i < host->max_id; ++i)
			scsi_report_device_reset(host, 0, i);
	}
}