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
struct scm_request {int /*<<< orphan*/  list; void* aidaw; void* aob; } ;
struct aob_rq_header {scalar_t__ data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_DMA ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ __scm_alloc_rq_cluster (struct scm_request*) ; 
 int /*<<< orphan*/  __scm_free_rq (struct scm_request*) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inactive_requests ; 
 struct aob_rq_header* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __scm_alloc_rq(void)
{
	struct aob_rq_header *aobrq;
	struct scm_request *scmrq;

	aobrq = kzalloc(sizeof(*aobrq) + sizeof(*scmrq), GFP_KERNEL);
	if (!aobrq)
		return -ENOMEM;

	scmrq = (void *) aobrq->data;
	scmrq->aidaw = (void *) get_zeroed_page(GFP_DMA);
	scmrq->aob = (void *) get_zeroed_page(GFP_DMA);
	if (!scmrq->aob || !scmrq->aidaw) {
		__scm_free_rq(scmrq);
		return -ENOMEM;
	}

	if (__scm_alloc_rq_cluster(scmrq)) {
		__scm_free_rq(scmrq);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&scmrq->list);
	spin_lock_irq(&list_lock);
	list_add(&scmrq->list, &inactive_requests);
	spin_unlock_irq(&list_lock);

	return 0;
}