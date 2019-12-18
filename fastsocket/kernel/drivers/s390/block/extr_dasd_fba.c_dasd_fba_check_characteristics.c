#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int blk_bdsa; int blk_size; } ;
struct dasd_fba_private {TYPE_3__ rdc_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  opm; } ;
struct dasd_device {struct ccw_device* cdev; int /*<<< orphan*/  flags; TYPE_1__ path_data; int /*<<< orphan*/  default_expires; int /*<<< orphan*/ * private; struct dasd_block* block; } ;
struct dasd_block {struct dasd_device* base; } ;
struct TYPE_5__ {int /*<<< orphan*/  cu_model; int /*<<< orphan*/  cu_type; int /*<<< orphan*/  dev_model; int /*<<< orphan*/  dev_type; } ;
struct ccw_device {TYPE_2__ id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_EXPIRES ; 
 int /*<<< orphan*/  DASD_FBA_MAGIC ; 
 int /*<<< orphan*/  DASD_FLAG_DEVICE_RO ; 
 int /*<<< orphan*/  DBF_EVENT_DEVID (int /*<<< orphan*/ ,struct ccw_device*,char*,...) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dasd_block*) ; 
 int /*<<< orphan*/  LPM_ANYPATH ; 
 int PTR_ERR (struct dasd_block*) ; 
 struct dasd_block* dasd_alloc_block () ; 
 int dasd_device_is_ro (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_free_block (struct dasd_block*) ; 
 int dasd_generic_read_dev_chars (struct dasd_device*,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct dasd_fba_private*) ; 
 struct dasd_fba_private* kzalloc (int,int) ; 
 int /*<<< orphan*/  memset (struct dasd_fba_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dasd_fba_check_characteristics(struct dasd_device *device)
{
	struct dasd_block *block;
	struct dasd_fba_private *private;
	struct ccw_device *cdev = device->cdev;
	int rc;
	int readonly;

	private = (struct dasd_fba_private *) device->private;
	if (!private) {
		private = kzalloc(sizeof(*private), GFP_KERNEL | GFP_DMA);
		if (!private) {
			dev_warn(&device->cdev->dev,
				 "Allocating memory for private DASD "
				 "data failed\n");
			return -ENOMEM;
		}
		device->private = (void *) private;
	} else {
		memset(private, 0, sizeof(*private));
	}
	block = dasd_alloc_block();
	if (IS_ERR(block)) {
		DBF_EVENT_DEVID(DBF_WARNING, cdev, "%s", "could not allocate "
				"dasd block structure");
		device->private = NULL;
		kfree(private);
		return PTR_ERR(block);
	}
	device->block = block;
	block->base = device;

	/* Read Device Characteristics */
	rc = dasd_generic_read_dev_chars(device, DASD_FBA_MAGIC,
					 &private->rdc_data, 32);
	if (rc) {
		DBF_EVENT_DEVID(DBF_WARNING, cdev, "Read device "
				"characteristics returned error %d", rc);
		device->block = NULL;
		dasd_free_block(block);
		device->private = NULL;
		kfree(private);
		return rc;
	}

	device->default_expires = DASD_EXPIRES;
	device->path_data.opm = LPM_ANYPATH;

	readonly = dasd_device_is_ro(device);
	if (readonly)
		set_bit(DASD_FLAG_DEVICE_RO, &device->flags);

	dev_info(&device->cdev->dev,
		 "New FBA DASD %04X/%02X (CU %04X/%02X) with %d MB "
		 "and %d B/blk%s\n",
		 cdev->id.dev_type,
		 cdev->id.dev_model,
		 cdev->id.cu_type,
		 cdev->id.cu_model,
		 ((private->rdc_data.blk_bdsa *
		   (private->rdc_data.blk_size >> 9)) >> 11),
		 private->rdc_data.blk_size,
		 readonly ? ", read-only device" : "");
	return 0;
}