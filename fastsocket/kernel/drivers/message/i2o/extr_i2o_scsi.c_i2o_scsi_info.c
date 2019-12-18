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
struct i2o_scsi_host {TYPE_1__* iop; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */

__attribute__((used)) static const char *i2o_scsi_info(struct Scsi_Host *SChost)
{
	struct i2o_scsi_host *hostdata;
	hostdata = (struct i2o_scsi_host *)SChost->hostdata;
	return hostdata->iop->name;
}