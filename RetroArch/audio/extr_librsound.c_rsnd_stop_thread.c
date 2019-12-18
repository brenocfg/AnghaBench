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
struct TYPE_4__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  cond_mutex; int /*<<< orphan*/  cond; } ;
struct TYPE_5__ {TYPE_1__ thread; scalar_t__ thread_active; } ;
typedef  TYPE_2__ rsound_t ;

/* Variables and functions */
 int /*<<< orphan*/  RSD_DEBUG (char*) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sthread_join (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsnd_stop_thread(rsound_t *rd)
{
   if ( rd->thread_active )
   {

      RSD_DEBUG("[RSound] Shutting down thread.\n");

      slock_lock(rd->thread.cond_mutex);
      rd->thread_active = 0;
      scond_signal(rd->thread.cond);
      slock_unlock(rd->thread.cond_mutex);

      sthread_join(rd->thread.thread);
      RSD_DEBUG("[RSound] Thread joined successfully.\n");

      return 0;
   }
   else
   {
      RSD_DEBUG("Thread is already shut down.\n");
      return 0;
   }
}