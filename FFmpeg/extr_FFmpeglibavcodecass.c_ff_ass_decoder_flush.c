#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags2; TYPE_1__* priv_data; } ;
struct TYPE_4__ {scalar_t__ readorder; } ;
typedef  TYPE_1__ FFASSDecoderContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AV_CODEC_FLAG2_RO_FLUSH_NOOP ; 

void ff_ass_decoder_flush(AVCodecContext *avctx)
{
    FFASSDecoderContext *s = avctx->priv_data;
    if (!(avctx->flags2 & AV_CODEC_FLAG2_RO_FLUSH_NOOP))
        s->readorder = 0;
}