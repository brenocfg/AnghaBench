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
struct TYPE_3__ {int is_paused; int success; int /*<<< orphan*/  mainloop; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ pa_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  pa_stream_cork (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stream_success_cb ; 

__attribute__((used)) static bool pulse_start(void *data, bool is_shutdown)
{
   bool ret;
   pa_t *pa = (pa_t*)data;
   if (!pa->is_paused)
      return true;

   RARCH_LOG("[PulseAudio]: Unpausing.\n");

   pa->success = true; /* In case of spurious wakeup. Not critical. */
   pa_threaded_mainloop_lock(pa->mainloop);
   pa_stream_cork(pa->stream, false, stream_success_cb, pa);
   pa_threaded_mainloop_wait(pa->mainloop);
   ret = pa->success;
   pa_threaded_mainloop_unlock(pa->mainloop);
   pa->is_paused = false;
   return ret;
}