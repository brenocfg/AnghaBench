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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct wait_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (struct wait_queue**) ; 

__attribute__((used)) static void wake_up_func(unsigned long data)
{
#ifdef DECLARE_WAITQUEUE
  wait_queue_head_t  *sleep_wait_p = (wait_queue_head_t*)data;
#else
  struct wait_queue **sleep_wait_p = (struct wait_queue **)data;
#endif
  wake_up(sleep_wait_p);
}