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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  stop_sem; } ;
typedef  TYPE_1__ osi_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int osi_sem_take (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int osi_thread_join(osi_thread_t *thread, uint32_t wait_ms)
{
    assert(thread != NULL);
    return osi_sem_take(&thread->stop_sem, wait_ms);
}