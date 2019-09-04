#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pa_operation ;
struct TYPE_5__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  mainloop; } ;
typedef  TYPE_1__ PulseData ;

/* Variables and functions */
 int /*<<< orphan*/ * pa_stream_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_lock (int /*<<< orphan*/ ) ; 
 int pulse_finish_stream_operation (TYPE_1__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pulse_stream_result ; 

__attribute__((used)) static int pulse_flash_stream(PulseData *s)
{
    pa_operation *op;
    pa_threaded_mainloop_lock(s->mainloop);
    op = pa_stream_flush(s->stream, pulse_stream_result, s);
    return pulse_finish_stream_operation(s, op, "pa_stream_flush");
}