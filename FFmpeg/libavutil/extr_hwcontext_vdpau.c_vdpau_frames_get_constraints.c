#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* nb_pix_fmts; } ;
typedef  TYPE_2__ VDPAUDeviceContext ;
struct TYPE_13__ {void* frames_sw_format; } ;
struct TYPE_12__ {TYPE_1__* internal; } ;
struct TYPE_11__ {void** valid_hw_formats; void** valid_sw_formats; } ;
struct TYPE_9__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ AVHWFramesConstraints ;
typedef  TYPE_4__ AVHWDeviceContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 void* AV_PIX_FMT_NONE ; 
 void* AV_PIX_FMT_VDPAU ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_ARRAY_ELEMS (TYPE_5__*) ; 
 void* av_malloc_array (int,int) ; 
 TYPE_5__* vdpau_pix_fmts ; 

__attribute__((used)) static int vdpau_frames_get_constraints(AVHWDeviceContext *ctx,
                                        const void *hwconfig,
                                        AVHWFramesConstraints *constraints)
{
    VDPAUDeviceContext   *priv  = ctx->internal->priv;
    int nb_sw_formats = 0;
    int i;

    constraints->valid_sw_formats = av_malloc_array(FF_ARRAY_ELEMS(vdpau_pix_fmts) + 1,
                                                    sizeof(*constraints->valid_sw_formats));
    if (!constraints->valid_sw_formats)
        return AVERROR(ENOMEM);

    for (i = 0; i < FF_ARRAY_ELEMS(vdpau_pix_fmts); i++) {
        if (priv->nb_pix_fmts[i] > 1)
            constraints->valid_sw_formats[nb_sw_formats++] = vdpau_pix_fmts[i].frames_sw_format;
    }
    constraints->valid_sw_formats[nb_sw_formats] = AV_PIX_FMT_NONE;

    constraints->valid_hw_formats = av_malloc_array(2, sizeof(*constraints->valid_hw_formats));
    if (!constraints->valid_hw_formats)
        return AVERROR(ENOMEM);

    constraints->valid_hw_formats[0] = AV_PIX_FMT_VDPAU;
    constraints->valid_hw_formats[1] = AV_PIX_FMT_NONE;

    return 0;
}