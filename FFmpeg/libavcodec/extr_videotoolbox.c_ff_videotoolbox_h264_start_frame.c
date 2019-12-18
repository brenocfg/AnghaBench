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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VTContext ;
struct TYPE_7__ {TYPE_2__* priv_data; TYPE_1__* internal; } ;
struct TYPE_6__ {int is_avc; } ;
struct TYPE_5__ {int /*<<< orphan*/ * hwaccel_priv_data; } ;
typedef  TYPE_2__ H264Context ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int videotoolbox_buffer_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int ff_videotoolbox_h264_start_frame(AVCodecContext *avctx,
                                     const uint8_t *buffer,
                                     uint32_t size)
{
    VTContext *vtctx = avctx->internal->hwaccel_priv_data;
    H264Context *h = avctx->priv_data;

    if (h->is_avc == 1) {
        return videotoolbox_buffer_copy(vtctx, buffer, size);
    }

    return 0;
}