#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ frame; int /*<<< orphan*/  bitstream; } ;
typedef  TYPE_2__ VTContext ;
struct TYPE_7__ {TYPE_1__* internal; } ;
struct TYPE_5__ {TYPE_2__* hwaccel_priv_data; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  CVPixelBufferRelease (scalar_t__) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

int ff_videotoolbox_uninit(AVCodecContext *avctx)
{
    VTContext *vtctx = avctx->internal->hwaccel_priv_data;
    if (vtctx) {
        av_freep(&vtctx->bitstream);
        if (vtctx->frame)
            CVPixelBufferRelease(vtctx->frame);
    }

    return 0;
}