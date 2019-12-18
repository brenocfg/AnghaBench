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
struct dm_kcopyd_throttle {int dummy; } ;
struct dm_kcopyd_client {int /*<<< orphan*/  job_pool; int /*<<< orphan*/  kcopyd_wq; int /*<<< orphan*/  nr_jobs; int /*<<< orphan*/  destroyq; int /*<<< orphan*/  io_client; scalar_t__ nr_free_pages; scalar_t__ nr_reserved_pages; int /*<<< orphan*/ * pages; int /*<<< orphan*/  kcopyd_work; int /*<<< orphan*/  unplug; struct dm_kcopyd_throttle* throttle; int /*<<< orphan*/  pages_jobs; int /*<<< orphan*/  io_jobs; int /*<<< orphan*/  complete_jobs; int /*<<< orphan*/  job_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct dm_kcopyd_client* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN_JOBS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESERVE_PAGES ; 
 int /*<<< orphan*/  _job_cache ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_free_pages (struct dm_kcopyd_client*) ; 
 int client_reserve_pages (struct dm_kcopyd_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_io_client_create () ; 
 int /*<<< orphan*/  do_work ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_kcopyd_client*) ; 
 struct dm_kcopyd_client* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_create_slab_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct dm_kcopyd_client *dm_kcopyd_client_create(struct dm_kcopyd_throttle *throttle)
{
	int r = -ENOMEM;
	struct dm_kcopyd_client *kc;

	kc = kmalloc(sizeof(*kc), GFP_KERNEL);
	if (!kc)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&kc->job_lock);
	INIT_LIST_HEAD(&kc->complete_jobs);
	INIT_LIST_HEAD(&kc->io_jobs);
	INIT_LIST_HEAD(&kc->pages_jobs);
	kc->throttle = throttle;

	memset(kc->unplug, 0, sizeof(kc->unplug));

	kc->job_pool = mempool_create_slab_pool(MIN_JOBS, _job_cache);
	if (!kc->job_pool)
		goto bad_slab;

	INIT_WORK(&kc->kcopyd_work, do_work);
	kc->kcopyd_wq = create_singlethread_workqueue("kcopyd");
	if (!kc->kcopyd_wq)
		goto bad_workqueue;

	kc->pages = NULL;
	kc->nr_reserved_pages = kc->nr_free_pages = 0;
	r = client_reserve_pages(kc, RESERVE_PAGES);
	if (r)
		goto bad_client_pages;

	kc->io_client = dm_io_client_create();
	if (IS_ERR(kc->io_client)) {
		r = PTR_ERR(kc->io_client);
		goto bad_io_client;
	}

	init_waitqueue_head(&kc->destroyq);
	atomic_set(&kc->nr_jobs, 0);

	return kc;

bad_io_client:
	client_free_pages(kc);
bad_client_pages:
	destroy_workqueue(kc->kcopyd_wq);
bad_workqueue:
	mempool_destroy(kc->job_pool);
bad_slab:
	kfree(kc);

	return ERR_PTR(r);
}