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
struct TYPE_3__ {int is_paused; int is_shutdown; } ;
typedef  TYPE_1__ audio_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  audio_driver_enable_callback () ; 
 int /*<<< orphan*/  audio_thread_unblock (TYPE_1__*) ; 

__attribute__((used)) static bool audio_thread_start(void *data, bool is_shutdown)
{
   audio_thread_t *thr = (audio_thread_t*)data;

   if (!thr)
      return false;

   audio_driver_enable_callback();

   thr->is_paused   = false;
   thr->is_shutdown = is_shutdown;
   audio_thread_unblock(thr);

   return true;
}