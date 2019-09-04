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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  pa_stream ;
typedef  size_t int64_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  mainloop; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ PulseData ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DEV_TO_APP_BUFFER_WRITABLE ; 
 int /*<<< orphan*/  avdevice_dev_to_app_control_message (TYPE_2__*,int /*<<< orphan*/ ,size_t*,int) ; 
 int /*<<< orphan*/  pa_threaded_mainloop_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pulse_stream_writable(pa_stream *stream, size_t nbytes, void *userdata)
{
    AVFormatContext *h = userdata;
    PulseData *s = h->priv_data;
    int64_t val = nbytes;

    if (stream != s->stream)
        return;

    avdevice_dev_to_app_control_message(h, AV_DEV_TO_APP_BUFFER_WRITABLE, &val, sizeof(val));
    pa_threaded_mainloop_signal(s->mainloop, 0);
}