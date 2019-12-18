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
struct TYPE_2__ {int /*<<< orphan*/  stream; scalar_t__ buffer_size; } ;
typedef  TYPE_1__ pa_t ;
typedef  int /*<<< orphan*/  pa_stream ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int,unsigned int) ; 
 scalar_t__ pa_stream_writable_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void underrun_update_cb(pa_stream *s, void *data)
{
#if 0
   pa_t *pa = (pa_t*)data;

   (void)s;

   RARCH_LOG("[PulseAudio]: Underrun (Buffer: %u, Writable size: %u).\n",
         (unsigned)pa->buffer_size,
         (unsigned)pa_stream_writable_size(pa->stream));
#endif
}