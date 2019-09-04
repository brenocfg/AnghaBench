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
struct TYPE_11__ {int /*<<< orphan*/  reset; } ;
typedef  TYPE_3__ VDPAUHWContext ;
struct TYPE_12__ {scalar_t__ device; scalar_t__ width; scalar_t__ height; } ;
typedef  TYPE_4__ VDPAUContext ;
struct TYPE_13__ {scalar_t__ coded_width; scalar_t__ coded_height; TYPE_1__* hwaccel; TYPE_2__* internal; TYPE_3__* hwaccel_context; } ;
struct TYPE_10__ {TYPE_4__* hwaccel_priv_data; } ;
struct TYPE_9__ {int (* init ) (TYPE_5__*) ;int /*<<< orphan*/  (* uninit ) (TYPE_5__*) ;} ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ VDP_INVALID_HANDLE ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 
 int stub2 (TYPE_5__*) ; 

__attribute__((used)) static int ff_vdpau_common_reinit(AVCodecContext *avctx)
{
    VDPAUHWContext *hwctx = avctx->hwaccel_context;
    VDPAUContext *vdctx = avctx->internal->hwaccel_priv_data;

    if (vdctx->device == VDP_INVALID_HANDLE)
        return 0; /* Decoder created by user */
    if (avctx->coded_width == vdctx->width &&
        avctx->coded_height == vdctx->height && (!hwctx || !hwctx->reset))
        return 0;

    avctx->hwaccel->uninit(avctx);
    return avctx->hwaccel->init(avctx);
}