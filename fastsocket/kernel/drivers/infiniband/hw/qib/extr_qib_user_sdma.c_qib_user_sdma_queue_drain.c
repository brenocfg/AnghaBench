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
struct qib_user_sdma_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  sent; } ;
struct qib_pportdata {struct qib_devdata* dd; } ;
struct qib_devdata {TYPE_1__* pcidev; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int QIB_USER_SDMA_DRAIN_TIMEOUT ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int /*<<< orphan*/  qib_user_sdma_free_pkt_list (int /*<<< orphan*/ *,struct qib_user_sdma_queue*,struct list_head*) ; 
 int /*<<< orphan*/  qib_user_sdma_hwqueue_clean (struct qib_pportdata*) ; 
 int /*<<< orphan*/  qib_user_sdma_queue_clean (struct qib_pportdata*,struct qib_user_sdma_queue*) ; 

void qib_user_sdma_queue_drain(struct qib_pportdata *ppd,
			       struct qib_user_sdma_queue *pq)
{
	struct qib_devdata *dd = ppd->dd;
	int i;

	if (!pq)
		return;

	for (i = 0; i < QIB_USER_SDMA_DRAIN_TIMEOUT; i++) {
		mutex_lock(&pq->lock);
		if (list_empty(&pq->sent)) {
			mutex_unlock(&pq->lock);
			break;
		}
		qib_user_sdma_hwqueue_clean(ppd);
		qib_user_sdma_queue_clean(ppd, pq);
		mutex_unlock(&pq->lock);
		msleep(10);
	}

	if (!list_empty(&pq->sent)) {
		struct list_head free_list;

		qib_dev_err(dd, "user sdma lists not empty: forcing!\n");
		INIT_LIST_HEAD(&free_list);
		mutex_lock(&pq->lock);
		list_splice_init(&pq->sent, &free_list);
		qib_user_sdma_free_pkt_list(&dd->pcidev->dev, pq, &free_list);
		mutex_unlock(&pq->lock);
	}
}