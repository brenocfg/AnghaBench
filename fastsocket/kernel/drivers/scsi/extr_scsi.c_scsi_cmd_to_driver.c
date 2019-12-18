#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_driver {int dummy; } ;
struct scsi_cmnd {TYPE_2__* request; } ;
struct TYPE_4__ {TYPE_1__* rq_disk; } ;
struct TYPE_3__ {scalar_t__ private_data; } ;

/* Variables and functions */

__attribute__((used)) static struct scsi_driver *scsi_cmd_to_driver(struct scsi_cmnd *cmd)
{
	return *(struct scsi_driver **)cmd->request->rq_disk->private_data;
}