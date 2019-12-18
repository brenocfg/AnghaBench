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
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;
typedef  TYPE_1__* pthread_cond_t ;
struct TYPE_4__ {struct TYPE_4__* next; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int pthread_cond_broadcast (TYPE_1__**) ; 
 TYPE_1__* ptw32_cond_list_head ; 
 int /*<<< orphan*/  ptw32_cond_list_lock ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 

void *
pthread_timechange_handler_np (void *arg)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      Broadcasts all CVs to force re-evaluation and
      *      new timeouts if required.
      *
      * PARAMETERS
      *      NONE
      *
      *
      * DESCRIPTION
      *      Broadcasts all CVs to force re-evaluation and
      *      new timeouts if required.
      *
      *      This routine may be passed directly to pthread_create()
      *      as a new thread in order to run asynchronously.
      *
      *
      * RESULTS
      *              0               successfully broadcast all CVs
      *              EAGAIN          Not all CVs were broadcast
      *
      * ------------------------------------------------------
      */
{
  int result = 0;
  pthread_cond_t cv;
  ptw32_mcs_local_node_t node;

  ptw32_mcs_lock_acquire(&ptw32_cond_list_lock, &node);

  cv = ptw32_cond_list_head;

  while (cv != NULL && 0 == result)
    {
      result = pthread_cond_broadcast (&cv);
      cv = cv->next;
    }

  ptw32_mcs_lock_release(&node);

  return (void *) (size_t) (result != 0 ? EAGAIN : 0);
}