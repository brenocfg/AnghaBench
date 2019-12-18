#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ pa_t ;

/* Variables and functions */
 int /*<<< orphan*/  audio_driver_set_buffer_size (int /*<<< orphan*/ ) ; 
 size_t pa_stream_writable_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t pulse_write_avail(void *data)
{
   size_t length;
   pa_t *pa = (pa_t*)data;

   pa_threaded_mainloop_lock(pa->mainloop);
   length = pa_stream_writable_size(pa->stream);

   audio_driver_set_buffer_size(pa->buffer_size); /* Can change spuriously. */
   pa_threaded_mainloop_unlock(pa->mainloop);
   return length;
}