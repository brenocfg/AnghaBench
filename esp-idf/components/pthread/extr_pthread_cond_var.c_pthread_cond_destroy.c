#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pthread_cond_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  waiter_list; } ;
typedef  TYPE_1__ esp_pthread_cond_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_acquire_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_close_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int pthread_cond_destroy(pthread_cond_t *cv)
{
    int ret = 0;

    if (cv == NULL || *cv == (pthread_cond_t) 0) {
        return EINVAL;
    }

    esp_pthread_cond_t *cond = (esp_pthread_cond_t *) *cv;

    _lock_acquire_recursive(&cond->lock);
    if (!TAILQ_EMPTY(&cond->waiter_list)) {
        ret = EBUSY;
    }
    _lock_release_recursive(&cond->lock);

    if (ret == 0) {
        *cv = (pthread_cond_t) 0;
        _lock_close_recursive(&cond->lock);
        free(cond);
    }

    return ret;
}