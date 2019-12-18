#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vdpau_picture_context {int dummy; } ;
struct TYPE_8__ {TYPE_3__* frames; } ;
typedef  TYPE_2__ VP9SharedContext ;
struct TYPE_7__ {int /*<<< orphan*/  f; } ;
struct TYPE_9__ {TYPE_1__ tf; struct vdpau_picture_context* hwaccel_picture_private; } ;
typedef  TYPE_3__ VP9Frame ;
struct TYPE_10__ {TYPE_2__* priv_data; } ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 size_t CUR_FRAME ; 
 int ff_vdpau_common_end_frame (TYPE_4__*,int /*<<< orphan*/ ,struct vdpau_picture_context*) ; 

__attribute__((used)) static int vdpau_vp9_end_frame(AVCodecContext *avctx)
{
    VP9SharedContext *h = avctx->priv_data;
    VP9Frame pic = h->frames[CUR_FRAME];
    struct vdpau_picture_context *pic_ctx = pic.hwaccel_picture_private;

    int val;

    val = ff_vdpau_common_end_frame(avctx, pic.tf.f, pic_ctx);
    if (val < 0)
        return val;

    return 0;
}