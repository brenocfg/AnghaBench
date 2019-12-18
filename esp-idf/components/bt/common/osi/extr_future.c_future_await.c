#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* result; scalar_t__ semaphore; } ;
typedef  TYPE_1__ future_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSI_SEM_MAX_TIMEOUT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  future_free (TYPE_1__*) ; 
 int /*<<< orphan*/  osi_sem_take (scalar_t__*,int /*<<< orphan*/ ) ; 

void *future_await(future_t *future)
{
    assert(future != NULL);

    // If the future is immediate, it will not have a semaphore
    if (future->semaphore) {
        osi_sem_take(&future->semaphore, OSI_SEM_MAX_TIMEOUT);
    }

    void *result = future->result;
    future_free(future);
    return result;
}