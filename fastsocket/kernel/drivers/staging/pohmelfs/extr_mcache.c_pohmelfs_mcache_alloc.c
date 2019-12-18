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
typedef  int /*<<< orphan*/  u64 ;
struct pohmelfs_sb {int /*<<< orphan*/  mcache_lock; int /*<<< orphan*/  mcache_gen; } ;
struct pohmelfs_mcache {unsigned int size; int /*<<< orphan*/  gen; int /*<<< orphan*/  start; void* data; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  err; int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct pohmelfs_mcache* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_long_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct pohmelfs_mcache* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct pohmelfs_mcache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pohmelfs_mcache_insert (struct pohmelfs_sb*,struct pohmelfs_mcache*) ; 
 int /*<<< orphan*/  pohmelfs_mcache_pool ; 

struct pohmelfs_mcache *pohmelfs_mcache_alloc(struct pohmelfs_sb *psb, u64 start,
		unsigned int size, void *data)
{
	struct pohmelfs_mcache *m;
	int err = -ENOMEM;

	m = mempool_alloc(pohmelfs_mcache_pool, GFP_KERNEL);
	if (!m)
		goto err_out_exit;

	init_completion(&m->complete);
	m->err = 0;
	atomic_set(&m->refcnt, 1);
	m->data = data;
	m->start = start;
	m->size = size;
	m->gen = atomic_long_inc_return(&psb->mcache_gen);

	mutex_lock(&psb->mcache_lock);
	err = pohmelfs_mcache_insert(psb, m);
	mutex_unlock(&psb->mcache_lock);
	if (err)
		goto err_out_free;

	return m;

err_out_free:
	mempool_free(m, pohmelfs_mcache_pool);
err_out_exit:
	return ERR_PTR(err);
}