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
struct request_queue {int dummy; } ;
struct i2o_block_device {struct gendisk* gd; int /*<<< orphan*/  lock; int /*<<< orphan*/  wcache; int /*<<< orphan*/  rcache; int /*<<< orphan*/  open_queue; } ;
struct gendisk {struct i2o_block_device* private_data; int /*<<< orphan*/ * fops; struct request_queue* queue; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_PREFETCH ; 
 int /*<<< orphan*/  CACHE_WRITEBACK ; 
 int ENOMEM ; 
 struct i2o_block_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2O_MAJOR ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct gendisk* alloc_disk (int) ; 
 struct request_queue* blk_init_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_prep_rq (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2o_block_fops ; 
 int /*<<< orphan*/  i2o_block_prep_req_fn ; 
 int /*<<< orphan*/  i2o_block_request_fn ; 
 int /*<<< orphan*/  kfree (struct i2o_block_device*) ; 
 struct i2o_block_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_err (char*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct i2o_block_device *i2o_block_device_alloc(void)
{
	struct i2o_block_device *dev;
	struct gendisk *gd;
	struct request_queue *queue;
	int rc;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		osm_err("Insufficient memory to allocate I2O Block disk.\n");
		rc = -ENOMEM;
		goto exit;
	}

	INIT_LIST_HEAD(&dev->open_queue);
	spin_lock_init(&dev->lock);
	dev->rcache = CACHE_PREFETCH;
	dev->wcache = CACHE_WRITEBACK;

	/* allocate a gendisk with 16 partitions */
	gd = alloc_disk(16);
	if (!gd) {
		osm_err("Insufficient memory to allocate gendisk.\n");
		rc = -ENOMEM;
		goto cleanup_dev;
	}

	/* initialize the request queue */
	queue = blk_init_queue(i2o_block_request_fn, &dev->lock);
	if (!queue) {
		osm_err("Insufficient memory to allocate request queue.\n");
		rc = -ENOMEM;
		goto cleanup_queue;
	}

	blk_queue_prep_rq(queue, i2o_block_prep_req_fn);

	gd->major = I2O_MAJOR;
	gd->queue = queue;
	gd->fops = &i2o_block_fops;
	gd->private_data = dev;

	dev->gd = gd;

	return dev;

      cleanup_queue:
	put_disk(gd);

      cleanup_dev:
	kfree(dev);

      exit:
	return ERR_PTR(rc);
}