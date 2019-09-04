#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVInputFormat ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  int /*<<< orphan*/  AVDeviceInfoList ;

/* Variables and functions */
 int ff_alloc_input_device_context (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int list_devices_for_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int avdevice_list_input_sources(AVInputFormat *device, const char *device_name,
                                AVDictionary *device_options, AVDeviceInfoList **device_list)
{
    AVFormatContext *s = NULL;
    int ret;

    if ((ret = ff_alloc_input_device_context(&s, device, device_name)) < 0)
        return ret;
    return list_devices_for_context(s, device_options, device_list);
}