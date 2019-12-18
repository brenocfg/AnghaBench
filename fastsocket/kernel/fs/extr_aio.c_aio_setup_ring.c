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
struct page {int dummy; } ;
struct aio_ring_info {unsigned int nr; int mmap_size; int mmap_base; int nr_pages; int /*<<< orphan*/ * ring_pages; int /*<<< orphan*/ * internal_pages; } ;
struct kioctx {unsigned int max_reqs; int user_id; TYPE_1__* mm; struct aio_ring_info ring_info; } ;
struct io_event {int dummy; } ;
struct aio_ring {unsigned int nr; int id; int header_length; int /*<<< orphan*/  incompat_features; int /*<<< orphan*/  compat_features; int /*<<< orphan*/  magic; scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_RING_COMPAT_FEATURES ; 
 int /*<<< orphan*/  AIO_RING_INCOMPAT_FEATURES ; 
 int /*<<< orphan*/  AIO_RING_MAGIC ; 
 int AIO_RING_PAGES ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int MAP_ANONYMOUS ; 
 int MAP_PRIVATE ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  aio_free_ring (struct kioctx*) ; 
 int /*<<< orphan*/  current ; 
 int do_mmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int get_user_pages (int /*<<< orphan*/ ,TYPE_1__*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct aio_ring* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (struct aio_ring*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aio_setup_ring(struct kioctx *ctx)
{
	struct aio_ring *ring;
	struct aio_ring_info *info = &ctx->ring_info;
	unsigned nr_events = ctx->max_reqs;
	unsigned long size;
	int nr_pages;

	/* Compensate for the ring buffer's head/tail overlap entry */
	nr_events += 2;	/* 1 is required, 2 for good luck */

	size = sizeof(struct aio_ring);
	size += sizeof(struct io_event) * nr_events;
	nr_pages = (size + PAGE_SIZE-1) >> PAGE_SHIFT;

	if (nr_pages < 0)
		return -EINVAL;

	nr_events = (PAGE_SIZE * nr_pages - sizeof(struct aio_ring)) / sizeof(struct io_event);

	info->nr = 0;
	info->ring_pages = info->internal_pages;
	if (nr_pages > AIO_RING_PAGES) {
		info->ring_pages = kcalloc(nr_pages, sizeof(struct page *), GFP_KERNEL);
		if (!info->ring_pages)
			return -ENOMEM;
	}

	info->mmap_size = nr_pages * PAGE_SIZE;
	dprintk("attempting mmap of %lu bytes\n", info->mmap_size);
	down_write(&ctx->mm->mmap_sem);
	info->mmap_base = do_mmap(NULL, 0, info->mmap_size, 
				  PROT_READ|PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE,
				  0);
	if (IS_ERR((void *)info->mmap_base)) {
		up_write(&ctx->mm->mmap_sem);
		info->mmap_size = 0;
		aio_free_ring(ctx);
		return -EAGAIN;
	}

	dprintk("mmap address: 0x%08lx\n", info->mmap_base);
	info->nr_pages = get_user_pages(current, ctx->mm,
					info->mmap_base, nr_pages, 
					1, 0, info->ring_pages, NULL);
	up_write(&ctx->mm->mmap_sem);

	if (unlikely(info->nr_pages != nr_pages)) {
		aio_free_ring(ctx);
		return -EAGAIN;
	}

	ctx->user_id = info->mmap_base;

	info->nr = nr_events;		/* trusted copy */

	ring = kmap_atomic(info->ring_pages[0], KM_USER0);
	ring->nr = nr_events;	/* user copy */
	ring->id = ctx->user_id;
	ring->head = ring->tail = 0;
	ring->magic = AIO_RING_MAGIC;
	ring->compat_features = AIO_RING_COMPAT_FEATURES;
	ring->incompat_features = AIO_RING_INCOMPAT_FEATURES;
	ring->header_length = sizeof(struct aio_ring);
	kunmap_atomic(ring, KM_USER0);

	return 0;
}