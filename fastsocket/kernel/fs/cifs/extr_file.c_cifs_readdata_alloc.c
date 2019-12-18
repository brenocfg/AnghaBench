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
struct slow_work_ops {int dummy; } ;
struct page {int dummy; } ;
struct cifs_readdata {int /*<<< orphan*/  work; int /*<<< orphan*/  done; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct cifs_readdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slow_work_init (int /*<<< orphan*/ *,struct slow_work_ops const*) ; 

__attribute__((used)) static struct cifs_readdata *
cifs_readdata_alloc(unsigned int nr_pages, const struct slow_work_ops *ops)
{
	struct cifs_readdata *rdata;

	rdata = kzalloc(sizeof(*rdata) + (sizeof(struct page *) * nr_pages),
			GFP_KERNEL);
	if (rdata != NULL) {
		kref_init(&rdata->refcount);
		INIT_LIST_HEAD(&rdata->list);
		init_completion(&rdata->done);
		slow_work_init(&rdata->work, ops);
	}

	return rdata;
}