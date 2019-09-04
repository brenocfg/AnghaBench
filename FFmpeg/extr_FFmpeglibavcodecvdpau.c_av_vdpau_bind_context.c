#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VdpGetProcAddress ;
typedef  int /*<<< orphan*/  VdpDevice ;
struct TYPE_7__ {int /*<<< orphan*/  decoder; } ;
struct TYPE_8__ {unsigned int flags; int reset; int /*<<< orphan*/ * get_proc_address; int /*<<< orphan*/  device; TYPE_1__ context; } ;
typedef  TYPE_2__ VDPAUHWContext ;
struct TYPE_9__ {TYPE_2__* hwaccel_context; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 unsigned int AV_HWACCEL_FLAG_ALLOW_HIGH_DEPTH ; 
 unsigned int AV_HWACCEL_FLAG_IGNORE_LEVEL ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  VDP_INVALID_HANDLE ; 
 scalar_t__ av_reallocp (TYPE_2__**,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int av_vdpau_bind_context(AVCodecContext *avctx, VdpDevice device,
                          VdpGetProcAddress *get_proc, unsigned flags)
{
    VDPAUHWContext *hwctx;

    if (flags & ~(AV_HWACCEL_FLAG_IGNORE_LEVEL|AV_HWACCEL_FLAG_ALLOW_HIGH_DEPTH))
        return AVERROR(EINVAL);

    if (av_reallocp(&avctx->hwaccel_context, sizeof(*hwctx)))
        return AVERROR(ENOMEM);

    hwctx = avctx->hwaccel_context;

    memset(hwctx, 0, sizeof(*hwctx));
    hwctx->context.decoder  = VDP_INVALID_HANDLE;
    hwctx->device           = device;
    hwctx->get_proc_address = get_proc;
    hwctx->flags            = flags;
    hwctx->reset            = 1;
    return 0;
}