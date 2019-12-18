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
struct i2o_scsi_host {int /*<<< orphan*/  scsi_host; } ;
struct i2o_controller {int /*<<< orphan*/ ** driver_data; } ;
struct TYPE_2__ {size_t context; } ;

/* Variables and functions */
 TYPE_1__ i2o_scsi_driver ; 
 struct i2o_scsi_host* i2o_scsi_get_host (struct i2o_controller*) ; 
 int /*<<< orphan*/  osm_debug (char*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2o_scsi_notify_controller_remove(struct i2o_controller *c)
{
	struct i2o_scsi_host *i2o_shost;
	i2o_shost = i2o_scsi_get_host(c);
	if (!i2o_shost)
		return;

	c->driver_data[i2o_scsi_driver.context] = NULL;

	scsi_remove_host(i2o_shost->scsi_host);
	scsi_host_put(i2o_shost->scsi_host);
	osm_debug("I2O SCSI host removed\n");
}