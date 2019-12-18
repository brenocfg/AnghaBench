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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  sem; } ;
typedef  TYPE_1__ VCOS_MSGQUEUE_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_mutex_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vcos_msgq_delete_internal(VCOS_MSGQUEUE_T *q)
{
   vcos_semaphore_delete(&q->sem);
   vcos_mutex_delete(&q->lock);
}