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
struct TYPE_5__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_4__ {TYPE_2__ ptHandle; int /*<<< orphan*/ * prevReuse; } ;
typedef  TYPE_1__ ptw32_thread_t ;
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;
typedef  TYPE_2__ pthread_t ;

/* Variables and functions */
 void* PTW32_THREAD_REUSE_EMPTY ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 void* ptw32_threadReuseBottom ; 
 void* ptw32_threadReuseTop ; 
 int /*<<< orphan*/  ptw32_thread_reuse_lock ; 

pthread_t
ptw32_threadReusePop (void)
{
  pthread_t t = {NULL, 0};
  ptw32_mcs_local_node_t node;

  ptw32_mcs_lock_acquire(&ptw32_thread_reuse_lock, &node);

  if (PTW32_THREAD_REUSE_EMPTY != ptw32_threadReuseTop)
    {
      ptw32_thread_t * tp;

      tp = ptw32_threadReuseTop;

      ptw32_threadReuseTop = tp->prevReuse;

      if (PTW32_THREAD_REUSE_EMPTY == ptw32_threadReuseTop)
        {
          ptw32_threadReuseBottom = PTW32_THREAD_REUSE_EMPTY;
        }

      tp->prevReuse = NULL;

      t = tp->ptHandle;
    }

  ptw32_mcs_lock_release(&node);

  return t;

}