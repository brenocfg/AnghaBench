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
struct io_context {TYPE_1__* aic; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dtor ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_long_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfq_dtor (struct io_context*) ; 
 int /*<<< orphan*/  iocontext_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct io_context*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

int put_io_context(struct io_context *ioc)
{
	if (ioc == NULL)
		return 1;

	BUG_ON(atomic_long_read(&ioc->refcount) == 0);

	if (atomic_long_dec_and_test(&ioc->refcount)) {
		rcu_read_lock();
		if (ioc->aic && ioc->aic->dtor)
			ioc->aic->dtor(ioc->aic);
		cfq_dtor(ioc);
		rcu_read_unlock();

		kmem_cache_free(iocontext_cachep, ioc);
		return 1;
	}
	return 0;
}