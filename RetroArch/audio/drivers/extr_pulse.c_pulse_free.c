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
struct TYPE_3__ {scalar_t__ mainloop; scalar_t__ context; scalar_t__ stream; } ;
typedef  TYPE_1__ pa_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pa_context_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  pa_context_unref (scalar_t__) ; 
 int /*<<< orphan*/  pa_stream_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  pa_stream_unref (scalar_t__) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_free (scalar_t__) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_stop (scalar_t__) ; 

__attribute__((used)) static void pulse_free(void *data)
{
   pa_t *pa = (pa_t*)data;

   if (!pa)
      return;

   if (pa->mainloop)
      pa_threaded_mainloop_stop(pa->mainloop);

   if (pa->stream)
   {
      pa_stream_disconnect(pa->stream);
      pa_stream_unref(pa->stream);
   }

   if (pa->context)
   {
      pa_context_disconnect(pa->context);
      pa_context_unref(pa->context);
   }

   if (pa->mainloop)
      pa_threaded_mainloop_free(pa->mainloop);

   free(pa);
}