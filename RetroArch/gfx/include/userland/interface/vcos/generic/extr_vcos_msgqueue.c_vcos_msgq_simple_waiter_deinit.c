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
struct TYPE_3__ {int /*<<< orphan*/  waitsem; } ;
typedef  TYPE_1__ VCOS_MSG_SIMPLE_WAITER_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vcos_msgq_simple_waiter_deinit(VCOS_MSG_SIMPLE_WAITER_T *waiter)
{
   vcos_semaphore_delete(&waiter->waitsem);
}