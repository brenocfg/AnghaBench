#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int is_avc; } ;
typedef  TYPE_1__ H264Context ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int videotoolbox_common_decode_slice (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int ff_videotoolbox_h264_decode_slice(AVCodecContext *avctx,
                                      const uint8_t *buffer,
                                      uint32_t size)
{
    H264Context *h = avctx->priv_data;

    if (h->is_avc == 1)
        return 0;

    return videotoolbox_common_decode_slice(avctx, buffer, size);
}