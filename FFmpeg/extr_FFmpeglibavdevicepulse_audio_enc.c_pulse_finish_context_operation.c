#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pa_operation ;
struct TYPE_4__ {int last_result; int /*<<< orphan*/  mainloop; } ;
typedef  TYPE_1__ PulseData ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pulse_finish_context_operation(PulseData *s, pa_operation *op, const char *name)
{
    if (!op) {
        pa_threaded_mainloop_unlock(s->mainloop);
        av_log(s, AV_LOG_ERROR, "%s failed.\n", name);
        return AVERROR_EXTERNAL;
    }
    s->last_result = 2;
    while (s->last_result == 2)
        pa_threaded_mainloop_wait(s->mainloop);
    pa_operation_unref(op);
    pa_threaded_mainloop_unlock(s->mainloop);
    if (s->last_result != 0)
        av_log(s, AV_LOG_ERROR, "%s failed.\n", name);
    return s->last_result;
}