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
struct TYPE_3__ {int counter; int /*<<< orphan*/  sema; scalar_t__ owner; scalar_t__ depth; } ;
typedef  TYPE_1__ __gthread_recursive_mutex_t ;

/* Variables and functions */
 int /*<<< orphan*/  CreateSemaphore (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
__gthr_win32_recursive_mutex_init_function (__gthread_recursive_mutex_t *mutex)
{
  mutex->counter = -1;
  mutex->depth = 0;
  mutex->owner = 0;
  mutex->sema = CreateSemaphore (NULL, 0, 65535, NULL);
}