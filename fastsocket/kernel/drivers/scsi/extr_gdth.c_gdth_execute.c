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
typedef  int /*<<< orphan*/  u32 ;
struct scsi_device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  gdth_cmd_str ;

/* Variables and functions */
 int __gdth_execute (struct scsi_device*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_free_host_dev (struct scsi_device*) ; 
 struct scsi_device* scsi_get_host_dev (struct Scsi_Host*) ; 

int gdth_execute(struct Scsi_Host *shost, gdth_cmd_str *gdtcmd, char *cmnd,
                 int timeout, u32 *info)
{
    struct scsi_device *sdev = scsi_get_host_dev(shost);
    int rval = __gdth_execute(sdev, gdtcmd, cmnd, timeout, info);

    scsi_free_host_dev(sdev);
    return rval;
}