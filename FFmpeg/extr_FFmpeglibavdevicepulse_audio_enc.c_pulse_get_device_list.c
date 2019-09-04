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
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ PulseData ;
typedef  TYPE_2__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDeviceInfoList ;

/* Variables and functions */
 int ff_pulse_audio_get_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pulse_get_device_list(AVFormatContext *h, AVDeviceInfoList *device_list)
{
    PulseData *s = h->priv_data;
    return ff_pulse_audio_get_devices(device_list, s->server, 1);
}