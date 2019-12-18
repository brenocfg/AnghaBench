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
struct dma_pool {int type; char* name; int /*<<< orphan*/  pools; int /*<<< orphan*/  dev_name; scalar_t__ nrefills; int /*<<< orphan*/  size; int /*<<< orphan*/  gfp_flags; scalar_t__ nfrees; scalar_t__ npages_in_use; scalar_t__ npages_free; struct device* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  inuse_list; int /*<<< orphan*/  free_list; struct dma_pool* pool; } ;
struct device_pools {int type; char* name; int /*<<< orphan*/  pools; int /*<<< orphan*/  dev_name; scalar_t__ nrefills; int /*<<< orphan*/  size; int /*<<< orphan*/  gfp_flags; scalar_t__ nfrees; scalar_t__ npages_in_use; scalar_t__ npages_free; struct device* dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  inuse_list; int /*<<< orphan*/  free_list; struct device_pools* pool; } ;
struct device {int /*<<< orphan*/  dma_pools; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum pool_type { ____Placeholder_pool_type } pool_type ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  npools; int /*<<< orphan*/  pools; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct dma_pool* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int IS_CACHED ; 
 int IS_DMA32 ; 
 int IS_UC ; 
 int IS_UNDEFINED ; 
 int IS_WC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__* _manager ; 
 char* dev_driver_string (struct device*) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_to_node (struct device*) ; 
 int /*<<< orphan*/  devres_add (struct device*,struct dma_pool**) ; 
 struct dma_pool** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct dma_pool**) ; 
 int /*<<< orphan*/  kfree (struct dma_pool*) ; 
 struct dma_pool* kmalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_dma_pool_release ; 

__attribute__((used)) static struct dma_pool *ttm_dma_pool_init(struct device *dev, gfp_t flags,
					  enum pool_type type)
{
	char *n[] = {"wc", "uc", "cached", " dma32", "unknown",};
	enum pool_type t[] = {IS_WC, IS_UC, IS_CACHED, IS_DMA32, IS_UNDEFINED};
	struct device_pools *sec_pool = NULL;
	struct dma_pool *pool = NULL, **ptr;
	unsigned i;
	int ret = -ENODEV;
	char *p;

	if (!dev)
		return NULL;

	ptr = devres_alloc(ttm_dma_pool_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return NULL;

	ret = -ENOMEM;

	pool = kmalloc_node(sizeof(struct dma_pool), GFP_KERNEL,
			    dev_to_node(dev));
	if (!pool)
		goto err_mem;

	sec_pool = kmalloc_node(sizeof(struct device_pools), GFP_KERNEL,
				dev_to_node(dev));
	if (!sec_pool)
		goto err_mem;

	INIT_LIST_HEAD(&sec_pool->pools);
	sec_pool->dev = dev;
	sec_pool->pool =  pool;

	INIT_LIST_HEAD(&pool->free_list);
	INIT_LIST_HEAD(&pool->inuse_list);
	INIT_LIST_HEAD(&pool->pools);
	spin_lock_init(&pool->lock);
	pool->dev = dev;
	pool->npages_free = pool->npages_in_use = 0;
	pool->nfrees = 0;
	pool->gfp_flags = flags;
	pool->size = PAGE_SIZE;
	pool->type = type;
	pool->nrefills = 0;
	p = pool->name;
	for (i = 0; i < 5; i++) {
		if (type & t[i]) {
			p += snprintf(p, sizeof(pool->name) - (p - pool->name),
				      "%s", n[i]);
		}
	}
	*p = 0;
	/* We copy the name for pr_ calls b/c when dma_pool_destroy is called
	 * - the kobj->name has already been deallocated.*/
	snprintf(pool->dev_name, sizeof(pool->dev_name), "%s %s",
		 dev_driver_string(dev), dev_name(dev));
	mutex_lock(&_manager->lock);
	/* You can get the dma_pool from either the global: */
	list_add(&sec_pool->pools, &_manager->pools);
	_manager->npools++;
	/* or from 'struct device': */
	list_add(&pool->pools, &dev->dma_pools);
	mutex_unlock(&_manager->lock);

	*ptr = pool;
	devres_add(dev, ptr);

	return pool;
err_mem:
	devres_free(ptr);
	kfree(sec_pool);
	kfree(pool);
	return ERR_PTR(ret);
}