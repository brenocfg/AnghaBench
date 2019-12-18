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
struct i2o_controller {struct i2o_scsi_host** driver_data; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {size_t context; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct i2o_scsi_host*) ; 
 TYPE_1__ i2o_scsi_driver ; 
 struct i2o_scsi_host* i2o_scsi_host_alloc (struct i2o_controller*) ; 
 int /*<<< orphan*/  osm_debug (char*) ; 
 int /*<<< orphan*/  osm_err (char*) ; 
 int scsi_add_host (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2o_scsi_notify_controller_add(struct i2o_controller *c)
{
	struct i2o_scsi_host *i2o_shost;
	int rc;

	i2o_shost = i2o_scsi_host_alloc(c);
	if (IS_ERR(i2o_shost)) {
		osm_err("Could not initialize SCSI host\n");
		return;
	}

	rc = scsi_add_host(i2o_shost->scsi_host, &c->device);
	if (rc) {
		osm_err("Could not add SCSI host\n");
		scsi_host_put(i2o_shost->scsi_host);
		return;
	}

	c->driver_data[i2o_scsi_driver.context] = i2o_shost;

	osm_debug("new I2O SCSI host added\n");
}