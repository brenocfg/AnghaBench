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
struct storvsc_cmd_request {int dummy; } ;
struct stor_mem_pools {int /*<<< orphan*/  request_pool; int /*<<< orphan*/  request_mempool; } ;
struct scsi_device {struct stor_mem_pools* hostdata; int /*<<< orphan*/  sdev_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int STORVSC_MIN_BUF_NR ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct stor_mem_pools*) ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 struct stor_mem_pools* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_alloc_slab ; 
 int /*<<< orphan*/  mempool_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free_slab ; 

__attribute__((used)) static int storvsc_device_alloc(struct scsi_device *sdevice)
{
	struct stor_mem_pools *memp;
	int number = STORVSC_MIN_BUF_NR;

	memp = kzalloc(sizeof(struct stor_mem_pools), GFP_KERNEL);
	if (!memp)
		return -ENOMEM;

	memp->request_pool =
		kmem_cache_create(dev_name(&sdevice->sdev_dev),
				sizeof(struct storvsc_cmd_request), 0,
				SLAB_HWCACHE_ALIGN, NULL);

	if (!memp->request_pool)
		goto err0;

	memp->request_mempool = mempool_create(number, mempool_alloc_slab,
						mempool_free_slab,
						memp->request_pool);

	if (!memp->request_mempool)
		goto err1;

	sdevice->hostdata = memp;

	return 0;

err1:
	kmem_cache_destroy(memp->request_pool);

err0:
	kfree(memp);
	return -ENOMEM;
}