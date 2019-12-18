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
struct proc_dir_entry {struct i2o_device* data; } ;
struct TYPE_3__ {int tid; int class_id; } ;
struct i2o_device {TYPE_1__ lct_data; TYPE_2__* iop; } ;
typedef  int /*<<< orphan*/  i2o_proc_entry ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  I2O_CLASS_RANDOM_BLOCK_STORAGE 129 
#define  I2O_CLASS_SCSI_PERIPHERAL 128 
 int /*<<< orphan*/ * generic_dev_entries ; 
 int /*<<< orphan*/  i2o_proc_create_entries (struct proc_dir_entry*,int /*<<< orphan*/ *,struct i2o_device*) ; 
 int /*<<< orphan*/  osm_debug (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  osm_warn (char*) ; 
 struct proc_dir_entry* proc_mkdir (char*,struct proc_dir_entry*) ; 
 int /*<<< orphan*/ * rbs_dev_entries ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void i2o_proc_device_add(struct proc_dir_entry *dir,
				struct i2o_device *dev)
{
	char buff[10];
	struct proc_dir_entry *devdir;
	i2o_proc_entry *i2o_pe = NULL;

	sprintf(buff, "%03x", dev->lct_data.tid);

	osm_debug("adding device /proc/i2o/%s/%s\n", dev->iop->name, buff);

	devdir = proc_mkdir(buff, dir);
	if (!devdir) {
		osm_warn("Could not allocate procdir!\n");
		return;
	}

	devdir->data = dev;

	i2o_proc_create_entries(devdir, generic_dev_entries, dev);

	/* Inform core that we want updates about this device's status */
	switch (dev->lct_data.class_id) {
	case I2O_CLASS_SCSI_PERIPHERAL:
	case I2O_CLASS_RANDOM_BLOCK_STORAGE:
		i2o_pe = rbs_dev_entries;
		break;
	default:
		break;
	}
	if (i2o_pe)
		i2o_proc_create_entries(devdir, i2o_pe, dev);
}