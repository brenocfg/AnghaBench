#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_8__ {TYPE_1__* internal; } ;
struct TYPE_7__ {scalar_t__ device_hwconfig_size; } ;
struct TYPE_6__ {TYPE_2__* hw_type; } ;
typedef  TYPE_2__ HWContextType ;
typedef  TYPE_3__ AVHWDeviceContext ;
typedef  TYPE_4__ AVBufferRef ;

/* Variables and functions */
 void* av_mallocz (scalar_t__) ; 

void *av_hwdevice_hwconfig_alloc(AVBufferRef *ref)
{
    AVHWDeviceContext *ctx = (AVHWDeviceContext*)ref->data;
    const HWContextType  *hw_type = ctx->internal->hw_type;

    if (hw_type->device_hwconfig_size == 0)
        return NULL;

    return av_mallocz(hw_type->device_hwconfig_size);
}