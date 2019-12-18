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

/* Variables and functions */
 int /*<<< orphan*/ * _runloop_msg_queue_lock ; 
 int /*<<< orphan*/  msg_queue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * runloop_msg_queue ; 
 int /*<<< orphan*/  runloop_msg_queue_lock () ; 
 int /*<<< orphan*/  runloop_msg_queue_unlock () ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void retroarch_msg_queue_deinit(void)
{
   runloop_msg_queue_lock();

   if (!runloop_msg_queue)
      return;

   msg_queue_free(runloop_msg_queue);

   runloop_msg_queue_unlock();
#ifdef HAVE_THREADS
   slock_free(_runloop_msg_queue_lock);
   _runloop_msg_queue_lock = NULL;
#endif

   runloop_msg_queue = NULL;
}