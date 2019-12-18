#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vdpau_picture_context {int dummy; } ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
struct TYPE_7__ {TYPE_1__* ref; } ;
struct TYPE_6__ {int /*<<< orphan*/  frame; struct vdpau_picture_context* hwaccel_picture_private; } ;
typedef  TYPE_2__ HEVCContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int ff_vdpau_common_end_frame (TYPE_3__*,int /*<<< orphan*/ ,struct vdpau_picture_context*) ; 

__attribute__((used)) static int vdpau_hevc_end_frame(AVCodecContext *avctx)
{
    HEVCContext *h = avctx->priv_data;
    struct vdpau_picture_context *pic_ctx = h->ref->hwaccel_picture_private;
    int val;

    val = ff_vdpau_common_end_frame(avctx, h->ref->frame, pic_ctx);
    if (val < 0)
        return val;

    return 0;
}