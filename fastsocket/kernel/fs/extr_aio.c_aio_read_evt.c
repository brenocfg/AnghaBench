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
struct aio_ring_info {unsigned long nr; int /*<<< orphan*/  ring_lock; int /*<<< orphan*/ * ring_pages; } ;
struct kioctx {struct aio_ring_info ring_info; } ;
struct io_event {int dummy; } ;
struct aio_ring {unsigned long head; unsigned long tail; scalar_t__ nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  KM_USER1 ; 
 struct io_event* aio_ring_event (struct aio_ring_info*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int,unsigned long,unsigned long) ; 
 struct aio_ring* kmap_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (struct aio_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_aio_ring_event (struct io_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aio_read_evt(struct kioctx *ioctx, struct io_event *ent)
{
	struct aio_ring_info *info = &ioctx->ring_info;
	struct aio_ring *ring;
	unsigned long head;
	int ret = 0;

	ring = kmap_atomic(info->ring_pages[0], KM_USER0);
	dprintk("in aio_read_evt h%lu t%lu m%lu\n",
		 (unsigned long)ring->head, (unsigned long)ring->tail,
		 (unsigned long)ring->nr);

	if (ring->head == ring->tail)
		goto out;

	spin_lock(&info->ring_lock);

	head = ring->head % info->nr;
	if (head != ring->tail) {
		struct io_event *evp = aio_ring_event(info, head, KM_USER1);
		*ent = *evp;
		head = (head + 1) % info->nr;
		smp_mb(); /* finish reading the event before updatng the head */
		ring->head = head;
		ret = 1;
		put_aio_ring_event(evp, KM_USER1);
	}
	spin_unlock(&info->ring_lock);

out:
	kunmap_atomic(ring, KM_USER0);
	dprintk("leaving aio_read_evt: %d  h%lu t%lu\n", ret,
		 (unsigned long)ring->head, (unsigned long)ring->tail);
	return ret;
}