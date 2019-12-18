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
struct pool {int /*<<< orphan*/  lock; } ;
struct dm_thin_new_mapping {int prepared; int /*<<< orphan*/  err; TYPE_1__* tc; } ;
struct TYPE_2__ {struct pool* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  __maybe_add_mapping (struct dm_thin_new_mapping*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void copy_complete(int read_err, unsigned long write_err, void *context)
{
	unsigned long flags;
	struct dm_thin_new_mapping *m = context;
	struct pool *pool = m->tc->pool;

	m->err = read_err || write_err ? -EIO : 0;

	spin_lock_irqsave(&pool->lock, flags);
	m->prepared = true;
	__maybe_add_mapping(m);
	spin_unlock_irqrestore(&pool->lock, flags);
}