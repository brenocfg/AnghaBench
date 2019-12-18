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
struct stor_mem_pools {int /*<<< orphan*/  request_pool; int /*<<< orphan*/  request_mempool; } ;
struct scsi_device {struct stor_mem_pools* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct stor_mem_pools*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void storvsc_device_destroy(struct scsi_device *sdevice)
{
	struct stor_mem_pools *memp = sdevice->hostdata;

	mempool_destroy(memp->request_mempool);
	kmem_cache_destroy(memp->request_pool);
	kfree(memp);
	sdevice->hostdata = NULL;
}