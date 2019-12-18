#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_12__ {int reconfig_needed; int /*<<< orphan*/ * sps; } ;
typedef  TYPE_4__ VTContext ;
struct TYPE_14__ {TYPE_5__* priv_data; TYPE_3__* internal; } ;
struct TYPE_10__ {TYPE_1__* sps; } ;
struct TYPE_13__ {TYPE_2__ ps; } ;
struct TYPE_11__ {TYPE_4__* hwaccel_priv_data; } ;
struct TYPE_9__ {int /*<<< orphan*/  const* data; } ;
typedef  TYPE_5__ H264Context ;
typedef  TYPE_6__ AVCodecContext ;

/* Variables and functions */
 int H264_NAL_SPS ; 
 int ff_videotoolbox_h264_decode_slice (TYPE_6__*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int videotoolbox_h264_decode_params(AVCodecContext *avctx,
                                           int type,
                                           const uint8_t *buffer,
                                           uint32_t size)
{
    VTContext *vtctx = avctx->internal->hwaccel_priv_data;
    H264Context *h = avctx->priv_data;

    // save sps header (profile/level) used to create decoder session
    if (!vtctx->sps[0])
        memcpy(vtctx->sps, h->ps.sps->data + 1, 3);

    if (type == H264_NAL_SPS) {
        if (size > 4 && memcmp(vtctx->sps, buffer + 1, 3) != 0) {
            vtctx->reconfig_needed = true;
            memcpy(vtctx->sps, buffer + 1, 3);
        }
    }

    // pass-through SPS/PPS changes to the decoder
    return ff_videotoolbox_h264_decode_slice(avctx, buffer, size);
}