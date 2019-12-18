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
struct TYPE_3__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  sema; int /*<<< orphan*/  stop_thread; } ;
typedef  TYPE_1__ MMAL_GRAPH_PRIVATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_TRUE ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_thread_join (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void graph_stop_worker_thread(MMAL_GRAPH_PRIVATE_T *graph)
{
   graph->stop_thread = MMAL_TRUE;
   vcos_semaphore_post(&graph->sema);
   vcos_thread_join(&graph->thread, NULL);
}