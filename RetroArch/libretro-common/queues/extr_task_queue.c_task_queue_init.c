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
typedef  void* retro_task_queue_msg_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* init ) () ;void* msg_push; } ;

/* Variables and functions */
 TYPE_1__* impl_current ; 
 TYPE_1__ impl_regular ; 
 TYPE_1__ impl_threaded ; 
 void* msg_push_bak ; 
 int /*<<< orphan*/  stub1 () ; 
 int task_threaded_enable ; 

void task_queue_init(bool threaded, retro_task_queue_msg_t msg_push)
{
   impl_current = &impl_regular;

#ifdef HAVE_THREADS
   if (threaded)
   {
      task_threaded_enable = true;
      impl_current         = &impl_threaded;
   }
#endif

   msg_push_bak            = msg_push;

   impl_current->msg_push  = msg_push;
   impl_current->init();
}