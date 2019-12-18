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
struct ipath_user_sdma_queue {int /*<<< orphan*/  pkt_slab; int /*<<< orphan*/  dma_pages_root; int /*<<< orphan*/  header_cache; int /*<<< orphan*/  header_cache_name; int /*<<< orphan*/  pkt_slab_name; int /*<<< orphan*/  lock; int /*<<< orphan*/  sent; scalar_t__ sent_counter; scalar_t__ counter; } ;
struct ipath_user_sdma_pkt {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPATH_USER_SDMA_EXP_HEADER_LENGTH ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  dma_pool_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipath_user_sdma_queue*) ; 
 struct ipath_user_sdma_queue* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 

struct ipath_user_sdma_queue *
ipath_user_sdma_queue_create(struct device *dev, int unit, int port, int sport)
{
	struct ipath_user_sdma_queue *pq =
		kmalloc(sizeof(struct ipath_user_sdma_queue), GFP_KERNEL);

	if (!pq)
		goto done;

	pq->counter = 0;
	pq->sent_counter = 0;
	INIT_LIST_HEAD(&pq->sent);

	mutex_init(&pq->lock);

	snprintf(pq->pkt_slab_name, sizeof(pq->pkt_slab_name),
		 "ipath-user-sdma-pkts-%u-%02u.%02u", unit, port, sport);
	pq->pkt_slab = kmem_cache_create(pq->pkt_slab_name,
					 sizeof(struct ipath_user_sdma_pkt),
					 0, 0, NULL);

	if (!pq->pkt_slab)
		goto err_kfree;

	snprintf(pq->header_cache_name, sizeof(pq->header_cache_name),
		 "ipath-user-sdma-headers-%u-%02u.%02u", unit, port, sport);
	pq->header_cache = dma_pool_create(pq->header_cache_name,
					   dev,
					   IPATH_USER_SDMA_EXP_HEADER_LENGTH,
					   4, 0);
	if (!pq->header_cache)
		goto err_slab;

	pq->dma_pages_root = RB_ROOT;

	goto done;

err_slab:
	kmem_cache_destroy(pq->pkt_slab);
err_kfree:
	kfree(pq);
	pq = NULL;

done:
	return pq;
}