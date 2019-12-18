#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int channels; scalar_t__ channel_layout; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (scalar_t__*) ; 
 scalar_t__* flac_channel_layouts ; 

void ff_flac_set_channel_layout(AVCodecContext *avctx)
{
    if (avctx->channels <= FF_ARRAY_ELEMS(flac_channel_layouts))
        avctx->channel_layout = flac_channel_layouts[avctx->channels - 1];
    else
        avctx->channel_layout = 0;
}