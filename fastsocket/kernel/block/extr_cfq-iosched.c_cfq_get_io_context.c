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
struct io_context {int /*<<< orphan*/  cgroup_changed; int /*<<< orphan*/  ioprio_changed; } ;
struct cfq_io_context {int dummy; } ;
struct cfq_data {TYPE_1__* queue; } ;
typedef  int gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int EEXIST ; 
 int __GFP_WAIT ; 
 struct cfq_io_context* cfq_alloc_io_context (struct cfq_data*,int) ; 
 int /*<<< orphan*/  cfq_cic_free (struct cfq_io_context*) ; 
 int cfq_cic_link (struct cfq_data*,struct io_context*,struct cfq_io_context*,int) ; 
 struct cfq_io_context* cfq_cic_lookup (struct cfq_data*,struct io_context*) ; 
 int /*<<< orphan*/  cfq_ioc_set_cgroup (struct io_context*) ; 
 int /*<<< orphan*/  cfq_ioc_set_ioprio (struct io_context*) ; 
 struct io_context* get_io_context (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 
 int /*<<< orphan*/  put_io_context (struct io_context*) ; 
 int /*<<< orphan*/  smp_read_barrier_depends () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cfq_io_context *
cfq_get_io_context(struct cfq_data *cfqd, gfp_t gfp_mask)
{
	struct io_context *ioc = NULL;
	struct cfq_io_context *cic;
	int ret;

	might_sleep_if(gfp_mask & __GFP_WAIT);

	ioc = get_io_context(gfp_mask, cfqd->queue->node);
	if (!ioc)
		return NULL;

retry:
	cic = cfq_cic_lookup(cfqd, ioc);
	if (cic)
		goto out;

	cic = cfq_alloc_io_context(cfqd, gfp_mask);
	if (cic == NULL)
		goto err;

	ret = cfq_cic_link(cfqd, ioc, cic, gfp_mask);
	if (ret == -EEXIST) {
		/* someone has linked cic to ioc already */
		cfq_cic_free(cic);
		goto retry;
	} else if (ret)
		goto err_free;

out:
	smp_read_barrier_depends();
	if (unlikely(ioc->ioprio_changed))
		cfq_ioc_set_ioprio(ioc);

#ifdef CONFIG_CFQ_GROUP_IOSCHED
	if (unlikely(ioc->cgroup_changed))
		cfq_ioc_set_cgroup(ioc);
#endif
	return cic;
err_free:
	cfq_cic_free(cic);
err:
	put_io_context(ioc);
	return NULL;
}