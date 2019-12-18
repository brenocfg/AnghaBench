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
struct TYPE_4__ {scalar_t__ semaphore; } ;
typedef  TYPE_1__ future_t ;

/* Variables and functions */
 int /*<<< orphan*/  osi_free (TYPE_1__*) ; 
 int /*<<< orphan*/  osi_sem_free (scalar_t__*) ; 

void future_free(future_t *future)
{
    if (!future) {
        return;
    }

    if (future->semaphore) {
        osi_sem_free(&future->semaphore);
    }

    osi_free(future);
}