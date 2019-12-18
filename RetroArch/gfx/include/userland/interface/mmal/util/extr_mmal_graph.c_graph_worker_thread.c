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
struct TYPE_4__ {scalar_t__ stop_thread; int /*<<< orphan*/  sema; } ;
typedef  TYPE_1__ MMAL_GRAPH_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_TRACE (char*,TYPE_1__*) ; 
 scalar_t__ graph_do_processing (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* graph_worker_thread(void* ctx)
{
   MMAL_GRAPH_PRIVATE_T *graph = (MMAL_GRAPH_PRIVATE_T *)ctx;

   while (1)
   {
      vcos_semaphore_wait(&graph->sema);
      if (graph->stop_thread)
         break;
      while(graph_do_processing(graph));
   }

   LOG_TRACE("worker thread exit %p", graph);

   return 0;
}