#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_3__* device_context; } ;
struct TYPE_16__ {TYPE_2__* oformat; TYPE_1__* iformat; int /*<<< orphan*/  priv_data; } ;
struct TYPE_15__ {int (* create_device_capabilities ) (TYPE_3__*,TYPE_4__*) ;} ;
struct TYPE_14__ {int (* create_device_capabilities ) (TYPE_3__*,TYPE_4__*) ;} ;
typedef  TYPE_3__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_4__ AVDeviceCapabilitiesQuery ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 
 TYPE_4__* av_mallocz (int) ; 
 int /*<<< orphan*/  av_opt_set_defaults (TYPE_4__*) ; 
 int av_opt_set_dict (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int stub1 (TYPE_3__*,TYPE_4__*) ; 
 int stub2 (TYPE_3__*,TYPE_4__*) ; 

int avdevice_capabilities_create(AVDeviceCapabilitiesQuery **caps, AVFormatContext *s,
                                 AVDictionary **device_options)
{
    int ret;
    av_assert0(s && caps);
    av_assert0(s->iformat || s->oformat);
    if ((s->oformat && !s->oformat->create_device_capabilities) ||
        (s->iformat && !s->iformat->create_device_capabilities))
        return AVERROR(ENOSYS);
    *caps = av_mallocz(sizeof(**caps));
    if (!(*caps))
        return AVERROR(ENOMEM);
    (*caps)->device_context = s;
    if (((ret = av_opt_set_dict(s->priv_data, device_options)) < 0))
        goto fail;
    if (s->iformat) {
        if ((ret = s->iformat->create_device_capabilities(s, *caps)) < 0)
            goto fail;
    } else {
        if ((ret = s->oformat->create_device_capabilities(s, *caps)) < 0)
            goto fail;
    }
    av_opt_set_defaults(*caps);
    return 0;
  fail:
    av_freep(caps);
    return ret;
}