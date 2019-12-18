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
struct TYPE_10__ {void* device_name; void* device_description; } ;
struct TYPE_9__ {int error_code; TYPE_1__* devices; } ;
struct TYPE_8__ {int /*<<< orphan*/  nb_devices; int /*<<< orphan*/  devices; } ;
typedef  TYPE_2__ PulseAudioDeviceList ;
typedef  TYPE_3__ AVDeviceInfo ;

/* Variables and functions */
 void* AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_dynarray_add_nofree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 int /*<<< orphan*/  av_freep (void**) ; 
 TYPE_3__* av_mallocz (int) ; 
 void* av_strdup (char const*) ; 

__attribute__((used)) static void pulse_add_detected_device(PulseAudioDeviceList *info,
                                      const char *name, const char *description)
{
    int ret;
    AVDeviceInfo *new_device = NULL;

    if (info->error_code)
        return;

    new_device = av_mallocz(sizeof(AVDeviceInfo));
    if (!new_device) {
        info->error_code = AVERROR(ENOMEM);
        return;
    }

    new_device->device_description = av_strdup(description);
    new_device->device_name = av_strdup(name);

    if (!new_device->device_description || !new_device->device_name) {
        info->error_code = AVERROR(ENOMEM);
        goto fail;
    }

    if ((ret = av_dynarray_add_nofree(&info->devices->devices,
                                      &info->devices->nb_devices, new_device)) < 0) {
        info->error_code = ret;
        goto fail;
    }
    return;

  fail:
    av_freep(&new_device->device_description);
    av_freep(&new_device->device_name);
    av_free(new_device);

}