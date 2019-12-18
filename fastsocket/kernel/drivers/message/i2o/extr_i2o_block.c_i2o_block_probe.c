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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct request_queue {int /*<<< orphan*/  max_hw_segments; int /*<<< orphan*/  max_phys_segments; int /*<<< orphan*/  max_sectors; struct i2o_block_device* queuedata; } ;
struct TYPE_2__ {int user_tid; int /*<<< orphan*/  tid; } ;
struct i2o_device {TYPE_1__ lct_data; int /*<<< orphan*/  device; struct i2o_controller* iop; } ;
struct i2o_controller {scalar_t__ limit_sectors; scalar_t__ adaptec; } ;
struct i2o_block_device {int power; struct gendisk* gd; struct i2o_device* i2o_dev; } ;
struct gendisk {int first_minor; int /*<<< orphan*/  disk_name; struct request_queue* queue; int /*<<< orphan*/ * driverfs_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 unsigned short I2O_MAX_SECTORS ; 
 unsigned short I2O_MAX_SECTORS_LIMITED ; 
 scalar_t__ IS_ERR (struct i2o_block_device*) ; 
 int KERNEL_SECTOR_SHIFT ; 
 int PTR_ERR (struct i2o_block_device*) ; 
 int /*<<< orphan*/  add_disk (struct gendisk*) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,unsigned short) ; 
 int /*<<< orphan*/  blk_queue_max_segments (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct i2o_block_device*) ; 
 struct i2o_block_device* i2o_block_device_alloc () ; 
 int /*<<< orphan*/  i2o_block_driver ; 
 scalar_t__ i2o_device_claim (struct i2o_device*) ; 
 int /*<<< orphan*/  i2o_device_claim_release (struct i2o_device*) ; 
 int /*<<< orphan*/  i2o_event_register (struct i2o_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2o_parm_field_get (struct i2o_device*,int,int,int*,int) ; 
 int /*<<< orphan*/  i2o_sg_tablesize (struct i2o_controller*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int) ; 
 int le64_to_cpu (int) ; 
 int /*<<< orphan*/  osm_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_err (char*) ; 
 int /*<<< orphan*/  osm_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_warn (char*,...) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char) ; 
 struct i2o_device* to_i2o_device (struct device*) ; 

__attribute__((used)) static int i2o_block_probe(struct device *dev)
{
	struct i2o_device *i2o_dev = to_i2o_device(dev);
	struct i2o_controller *c = i2o_dev->iop;
	struct i2o_block_device *i2o_blk_dev;
	struct gendisk *gd;
	struct request_queue *queue;
	static int unit = 0;
	int rc;
	u64 size;
	u32 blocksize;
	u16 body_size = 4;
	u16 power;
	unsigned short max_sectors;

#ifdef CONFIG_I2O_EXT_ADAPTEC
	if (c->adaptec)
		body_size = 8;
#endif

	if (c->limit_sectors)
		max_sectors = I2O_MAX_SECTORS_LIMITED;
	else
		max_sectors = I2O_MAX_SECTORS;

	/* skip devices which are used by IOP */
	if (i2o_dev->lct_data.user_tid != 0xfff) {
		osm_debug("skipping used device %03x\n", i2o_dev->lct_data.tid);
		return -ENODEV;
	}

	if (i2o_device_claim(i2o_dev)) {
		osm_warn("Unable to claim device. Installation aborted\n");
		rc = -EFAULT;
		goto exit;
	}

	i2o_blk_dev = i2o_block_device_alloc();
	if (IS_ERR(i2o_blk_dev)) {
		osm_err("could not alloc a new I2O block device");
		rc = PTR_ERR(i2o_blk_dev);
		goto claim_release;
	}

	i2o_blk_dev->i2o_dev = i2o_dev;
	dev_set_drvdata(dev, i2o_blk_dev);

	/* setup gendisk */
	gd = i2o_blk_dev->gd;
	gd->first_minor = unit << 4;
	sprintf(gd->disk_name, "i2o/hd%c", 'a' + unit);
	gd->driverfs_dev = &i2o_dev->device;

	/* setup request queue */
	queue = gd->queue;
	queue->queuedata = i2o_blk_dev;

	blk_queue_max_hw_sectors(queue, max_sectors);
	blk_queue_max_segments(queue, i2o_sg_tablesize(c, body_size));

	osm_debug("max sectors = %d\n", queue->max_sectors);
	osm_debug("phys segments = %d\n", queue->max_phys_segments);
	osm_debug("max hw segments = %d\n", queue->max_hw_segments);

	/*
	 *      Ask for the current media data. If that isn't supported
	 *      then we ask for the device capacity data
	 */
	if (!i2o_parm_field_get(i2o_dev, 0x0004, 1, &blocksize, 4) ||
	    !i2o_parm_field_get(i2o_dev, 0x0000, 3, &blocksize, 4)) {
		blk_queue_logical_block_size(queue, le32_to_cpu(blocksize));
	} else
		osm_warn("unable to get blocksize of %s\n", gd->disk_name);

	if (!i2o_parm_field_get(i2o_dev, 0x0004, 0, &size, 8) ||
	    !i2o_parm_field_get(i2o_dev, 0x0000, 4, &size, 8)) {
		set_capacity(gd, le64_to_cpu(size) >> KERNEL_SECTOR_SHIFT);
	} else
		osm_warn("could not get size of %s\n", gd->disk_name);

	if (!i2o_parm_field_get(i2o_dev, 0x0000, 2, &power, 2))
		i2o_blk_dev->power = power;

	i2o_event_register(i2o_dev, &i2o_block_driver, 0, 0xffffffff);

	add_disk(gd);

	unit++;

	osm_info("device added (TID: %03x): %s\n", i2o_dev->lct_data.tid,
		 i2o_blk_dev->gd->disk_name);

	return 0;

      claim_release:
	i2o_device_claim_release(i2o_dev);

      exit:
	return rc;
}