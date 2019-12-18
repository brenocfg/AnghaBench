#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* at_exit; scalar_t__ dummy; } ;
typedef  TYPE_2__ VCOS_THREAD_T ;
struct TYPE_5__ {int /*<<< orphan*/  cxt; int /*<<< orphan*/  (* pfn ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_free (TYPE_2__*) ; 
 int /*<<< orphan*/  vcos_thread_cleanup (TYPE_2__*) ; 

__attribute__((used)) static void vcos_dummy_thread_cleanup(void *cxt)
{
   VCOS_THREAD_T *thread = cxt;
   if (thread->dummy)
   {
      int i;
      /* call termination functions */
      for (i=0; thread->at_exit[i].pfn != NULL; i++)
      {
         thread->at_exit[i].pfn(thread->at_exit[i].cxt);
      }
      vcos_thread_cleanup(thread);
      vcos_free(thread);
   }
}