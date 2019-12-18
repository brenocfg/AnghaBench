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
struct ipath_user_sdma_queue {int /*<<< orphan*/  lock; } ;
struct ipath_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipath_user_sdma_hwqueue_clean (struct ipath_devdata*) ; 
 int ipath_user_sdma_queue_clean (struct ipath_devdata*,struct ipath_user_sdma_queue*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ipath_user_sdma_make_progress(struct ipath_devdata *dd,
				  struct ipath_user_sdma_queue *pq)
{
	int ret = 0;

	mutex_lock(&pq->lock);
	ipath_user_sdma_hwqueue_clean(dd);
	ret = ipath_user_sdma_queue_clean(dd, pq);
	mutex_unlock(&pq->lock);

	return ret;
}