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
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct ubifs_wbuf {int lnum; int offs; int avail; unsigned long long delta; int /*<<< orphan*/  softlimit; TYPE_1__ timer; scalar_t__ next_ino; struct ubifs_info* c; int /*<<< orphan*/  lock; int /*<<< orphan*/  io_mutex; int /*<<< orphan*/ * sync_callback; int /*<<< orphan*/  dtype; scalar_t__ used; int /*<<< orphan*/ * buf; void* inodes; } ;
struct ubifs_info {size_t min_io_size; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int UBIFS_CH_SZ ; 
 int /*<<< orphan*/  UBI_UNKNOWN ; 
 unsigned long long ULONG_MAX ; 
 unsigned long long WBUF_TIMEOUT_HARDLIMIT ; 
 unsigned long long WBUF_TIMEOUT_SOFTLIMIT ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_set (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  wbuf_timer_callback_nolock ; 

int ubifs_wbuf_init(struct ubifs_info *c, struct ubifs_wbuf *wbuf)
{
	size_t size;

	wbuf->buf = kmalloc(c->min_io_size, GFP_KERNEL);
	if (!wbuf->buf)
		return -ENOMEM;

	size = (c->min_io_size / UBIFS_CH_SZ + 1) * sizeof(ino_t);
	wbuf->inodes = kmalloc(size, GFP_KERNEL);
	if (!wbuf->inodes) {
		kfree(wbuf->buf);
		wbuf->buf = NULL;
		return -ENOMEM;
	}

	wbuf->used = 0;
	wbuf->lnum = wbuf->offs = -1;
	wbuf->avail = c->min_io_size;
	wbuf->dtype = UBI_UNKNOWN;
	wbuf->sync_callback = NULL;
	mutex_init(&wbuf->io_mutex);
	spin_lock_init(&wbuf->lock);
	wbuf->c = c;
	wbuf->next_ino = 0;

	hrtimer_init(&wbuf->timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	wbuf->timer.function = wbuf_timer_callback_nolock;
	wbuf->softlimit = ktime_set(WBUF_TIMEOUT_SOFTLIMIT, 0);
	wbuf->delta = WBUF_TIMEOUT_HARDLIMIT - WBUF_TIMEOUT_SOFTLIMIT;
	wbuf->delta *= 1000000000ULL;
	ubifs_assert(wbuf->delta <= ULONG_MAX);
	return 0;
}