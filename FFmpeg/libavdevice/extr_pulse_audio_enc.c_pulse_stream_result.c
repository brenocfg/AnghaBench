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
typedef  int /*<<< orphan*/  pa_stream ;
struct TYPE_2__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/  last_result; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ PulseData ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  pa_threaded_mainloop_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulse_stream_result(pa_stream *stream, int success, void *userdata)
{
    PulseData *s = userdata;

    if (stream != s->stream)
        return;

    s->last_result = success ? 0 : AVERROR_EXTERNAL;
    pa_threaded_mainloop_signal(s->mainloop, 0);
}