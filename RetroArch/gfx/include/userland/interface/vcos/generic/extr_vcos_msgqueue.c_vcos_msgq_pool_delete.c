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
struct TYPE_3__ {int /*<<< orphan*/  sem; int /*<<< orphan*/  blockpool; } ;
typedef  TYPE_1__ VCOS_MSGQ_POOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcos_blockpool_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_delete (int /*<<< orphan*/ *) ; 

void vcos_msgq_pool_delete(VCOS_MSGQ_POOL_T *pool)
{
   vcos_blockpool_delete(&pool->blockpool);
   vcos_semaphore_delete(&pool->sem);
}