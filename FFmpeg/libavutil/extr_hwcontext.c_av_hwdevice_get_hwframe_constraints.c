#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ data; } ;
struct TYPE_15__ {TYPE_1__* internal; } ;
struct TYPE_14__ {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; scalar_t__ min_height; scalar_t__ min_width; } ;
struct TYPE_13__ {scalar_t__ (* frames_get_constraints ) (TYPE_4__*,void const*,TYPE_3__*) ;} ;
struct TYPE_12__ {TYPE_2__* hw_type; } ;
typedef  TYPE_2__ HWContextType ;
typedef  TYPE_3__ AVHWFramesConstraints ;
typedef  TYPE_4__ AVHWDeviceContext ;
typedef  TYPE_5__ AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  av_hwframe_constraints_free (TYPE_3__**) ; 
 TYPE_3__* av_mallocz (int) ; 
 scalar_t__ stub1 (TYPE_4__*,void const*,TYPE_3__*) ; 

AVHWFramesConstraints *av_hwdevice_get_hwframe_constraints(AVBufferRef *ref,
                                                           const void *hwconfig)
{
    AVHWDeviceContext *ctx = (AVHWDeviceContext*)ref->data;
    const HWContextType  *hw_type = ctx->internal->hw_type;
    AVHWFramesConstraints *constraints;

    if (!hw_type->frames_get_constraints)
        return NULL;

    constraints = av_mallocz(sizeof(*constraints));
    if (!constraints)
        return NULL;

    constraints->min_width = constraints->min_height = 0;
    constraints->max_width = constraints->max_height = INT_MAX;

    if (hw_type->frames_get_constraints(ctx, hwconfig, constraints) >= 0) {
        return constraints;
    } else {
        av_hwframe_constraints_free(&constraints);
        return NULL;
    }
}