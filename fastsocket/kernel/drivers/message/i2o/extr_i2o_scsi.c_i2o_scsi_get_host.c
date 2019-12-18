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
struct i2o_scsi_host {int dummy; } ;
struct i2o_controller {struct i2o_scsi_host** driver_data; } ;
struct TYPE_2__ {size_t context; } ;

/* Variables and functions */
 TYPE_1__ i2o_scsi_driver ; 

__attribute__((used)) static struct i2o_scsi_host *i2o_scsi_get_host(struct i2o_controller *c)
{
	return c->driver_data[i2o_scsi_driver.context];
}