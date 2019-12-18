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
struct qib_user_sdma_queue {int /*<<< orphan*/  lock; } ;
struct qib_pportdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qib_user_sdma_hwqueue_clean (struct qib_pportdata*) ; 
 int qib_user_sdma_queue_clean (struct qib_pportdata*,struct qib_user_sdma_queue*) ; 

int qib_user_sdma_make_progress(struct qib_pportdata *ppd,
				struct qib_user_sdma_queue *pq)
{
	int ret = 0;

	mutex_lock(&pq->lock);
	qib_user_sdma_hwqueue_clean(ppd);
	ret = qib_user_sdma_queue_clean(ppd, pq);
	mutex_unlock(&pq->lock);

	return ret;
}