#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pthread_cond_t ;
struct TYPE_4__ {int /*<<< orphan*/  wait_sem; } ;
typedef  TYPE_1__ esp_pthread_cond_waiter_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  waiter_list; } ;
typedef  TYPE_2__ esp_pthread_cond_t ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_acquire_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _lock_release_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

int pthread_cond_signal(pthread_cond_t *cv)
{
    if (cv == NULL || *cv == (pthread_cond_t) 0) {
        return EINVAL;
    }

    esp_pthread_cond_t *cond = (esp_pthread_cond_t *) *cv;

    _lock_acquire_recursive(&cond->lock);
    esp_pthread_cond_waiter_t *entry;
    entry = TAILQ_FIRST(&cond->waiter_list);
    if (entry) {
        xSemaphoreGive(entry->wait_sem);
    }
    _lock_release_recursive(&cond->lock);

    return 0;
}