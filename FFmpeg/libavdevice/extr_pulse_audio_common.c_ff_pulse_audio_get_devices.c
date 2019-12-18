#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pa_operation ;
typedef  int /*<<< orphan*/  pa_mainloop ;
typedef  int /*<<< orphan*/  pa_context ;
typedef  enum pa_operation_state { ____Placeholder_pa_operation_state } pa_operation_state ;
struct TYPE_10__ {int nb_devices; int default_device; TYPE_1__** devices; } ;
struct TYPE_9__ {int output; scalar_t__ error_code; int /*<<< orphan*/  default_device; TYPE_3__* devices; int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  device_name; } ;
typedef  TYPE_2__ PulseAudioDeviceList ;
typedef  TYPE_3__ AVDeviceInfoList ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  EINVAL ; 
 int PA_OPERATION_DONE ; 
 int PA_OPERATION_RUNNING ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_pulse_audio_connect_context (int /*<<< orphan*/ **,int /*<<< orphan*/ **,char const*,char*) ; 
 int /*<<< orphan*/  ff_pulse_audio_disconnect_context (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * pa_context_get_server_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * pa_context_get_sink_info_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * pa_context_get_source_info_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pa_mainloop_iterate (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int pa_operation_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_operation_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pulse_audio_sink_device_cb ; 
 int /*<<< orphan*/  pulse_audio_source_device_cb ; 
 int /*<<< orphan*/  pulse_server_info_cb ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ff_pulse_audio_get_devices(AVDeviceInfoList *devices, const char *server, int output)
{
    pa_mainloop *pa_ml = NULL;
    pa_operation *pa_op = NULL;
    pa_context *pa_ctx = NULL;
    enum pa_operation_state op_state;
    PulseAudioDeviceList dev_list = { 0 };
    int i;

    dev_list.output = output;
    dev_list.devices = devices;
    if (!devices)
        return AVERROR(EINVAL);
    devices->nb_devices = 0;
    devices->devices = NULL;

    if ((dev_list.error_code = ff_pulse_audio_connect_context(&pa_ml, &pa_ctx, server, "Query devices")) < 0)
        goto fail;

    if (output)
        pa_op = pa_context_get_sink_info_list(pa_ctx, pulse_audio_sink_device_cb, &dev_list);
    else
        pa_op = pa_context_get_source_info_list(pa_ctx, pulse_audio_source_device_cb, &dev_list);
    while ((op_state = pa_operation_get_state(pa_op)) == PA_OPERATION_RUNNING)
        pa_mainloop_iterate(pa_ml, 1, NULL);
    if (op_state != PA_OPERATION_DONE)
        dev_list.error_code = AVERROR_EXTERNAL;
    pa_operation_unref(pa_op);
    if (dev_list.error_code < 0)
        goto fail;

    pa_op = pa_context_get_server_info(pa_ctx, pulse_server_info_cb, &dev_list);
    while ((op_state = pa_operation_get_state(pa_op)) == PA_OPERATION_RUNNING)
        pa_mainloop_iterate(pa_ml, 1, NULL);
    if (op_state != PA_OPERATION_DONE)
        dev_list.error_code = AVERROR_EXTERNAL;
    pa_operation_unref(pa_op);
    if (dev_list.error_code < 0)
        goto fail;

    devices->default_device = -1;
    for (i = 0; i < devices->nb_devices; i++) {
        if (!strcmp(devices->devices[i]->device_name, dev_list.default_device)) {
            devices->default_device = i;
            break;
        }
    }

  fail:
    av_free(dev_list.default_device);
    ff_pulse_audio_disconnect_context(&pa_ml, &pa_ctx);
    return dev_list.error_code;
}