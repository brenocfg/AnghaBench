#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* robustMxList; } ;
typedef  TYPE_3__ ptw32_thread_t ;
struct TYPE_11__ {struct TYPE_11__* next; TYPE_2__* prev; } ;
typedef  TYPE_4__ ptw32_robust_node_t ;
typedef  TYPE_5__* pthread_mutex_t ;
struct TYPE_8__ {TYPE_3__* p; } ;
struct TYPE_12__ {TYPE_1__ ownerThread; TYPE_4__* robustNode; } ;
struct TYPE_9__ {TYPE_4__* next; } ;

/* Variables and functions */

void
ptw32_robust_mutex_remove(pthread_mutex_t* mutex, ptw32_thread_t* otp)
{
  ptw32_robust_node_t** list;
  pthread_mutex_t mx = *mutex;
  ptw32_robust_node_t* robust = mx->robustNode;

  list = &(((ptw32_thread_t*)mx->ownerThread.p)->robustMxList);
  mx->ownerThread.p = otp;
  if (robust->next != NULL)
    {
      robust->next->prev = robust->prev;
    }
  if (robust->prev != NULL)
    {
      robust->prev->next = robust->next;
    }
  if (*list == robust)
    {
      *list = robust->next;
    }
}