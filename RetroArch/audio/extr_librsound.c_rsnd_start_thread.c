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
typedef  int /*<<< orphan*/  sthread_t ;
struct TYPE_5__ {int /*<<< orphan*/ * thread; } ;
struct TYPE_6__ {int thread_active; TYPE_1__ thread; scalar_t__ audio_callback; } ;
typedef  TYPE_2__ rsound_t ;

/* Variables and functions */
 int /*<<< orphan*/  RSD_ERR (char*) ; 
 int /*<<< orphan*/  rsnd_cb_thread ; 
 int /*<<< orphan*/  rsnd_thread ; 
 scalar_t__ sthread_create (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int rsnd_start_thread(rsound_t *rd)
{
   if ( !rd->thread_active )
   {
      rd->thread_active = 1;
      rd->thread.thread = (sthread_t*)sthread_create(rd->audio_callback ? rsnd_cb_thread : rsnd_thread, rd);
      if ( !rd->thread.thread )
      {
         rd->thread_active = 0;
         RSD_ERR("[RSound] Failed to create thread.");
         return -1;
      }
      return 0;
   }
   else
      return 0;
}