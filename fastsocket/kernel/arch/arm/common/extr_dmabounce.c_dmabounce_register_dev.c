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
struct TYPE_4__ {int /*<<< orphan*/  pool; } ;
struct dmabounce_device_info {TYPE_2__ small; int /*<<< orphan*/  attr_res; scalar_t__ bounce_count; scalar_t__ map_op_count; scalar_t__ total_allocs; int /*<<< orphan*/  lock; int /*<<< orphan*/  safe_buffers; struct device* dev; TYPE_2__ large; } ;
struct TYPE_3__ {struct dmabounce_device_info* dmabounce; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_dmabounce_stats ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ ) ; 
 int dmabounce_init_pool (TYPE_2__*,struct device*,char*,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct dmabounce_device_info*) ; 
 struct dmabounce_device_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

int dmabounce_register_dev(struct device *dev, unsigned long small_buffer_size,
		unsigned long large_buffer_size)
{
	struct dmabounce_device_info *device_info;
	int ret;

	device_info = kmalloc(sizeof(struct dmabounce_device_info), GFP_ATOMIC);
	if (!device_info) {
		dev_err(dev,
			"Could not allocated dmabounce_device_info\n");
		return -ENOMEM;
	}

	ret = dmabounce_init_pool(&device_info->small, dev,
				  "small_dmabounce_pool", small_buffer_size);
	if (ret) {
		dev_err(dev,
			"dmabounce: could not allocate DMA pool for %ld byte objects\n",
			small_buffer_size);
		goto err_free;
	}

	if (large_buffer_size) {
		ret = dmabounce_init_pool(&device_info->large, dev,
					  "large_dmabounce_pool",
					  large_buffer_size);
		if (ret) {
			dev_err(dev,
				"dmabounce: could not allocate DMA pool for %ld byte objects\n",
				large_buffer_size);
			goto err_destroy;
		}
	}

	device_info->dev = dev;
	INIT_LIST_HEAD(&device_info->safe_buffers);
	rwlock_init(&device_info->lock);

#ifdef STATS
	device_info->total_allocs = 0;
	device_info->map_op_count = 0;
	device_info->bounce_count = 0;
	device_info->attr_res = device_create_file(dev, &dev_attr_dmabounce_stats);
#endif

	dev->archdata.dmabounce = device_info;

	dev_info(dev, "dmabounce: registered device\n");

	return 0;

 err_destroy:
	dma_pool_destroy(device_info->small.pool);
 err_free:
	kfree(device_info);
	return ret;
}