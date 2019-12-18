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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {scalar_t__ out_format; TYPE_1__* avctx; } ;
struct TYPE_5__ {scalar_t__ lowres; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ FMT_MPEG1 ; 
 int /*<<< orphan*/  mpv_reconstruct_mb_internal (TYPE_2__*,int /*<<< orphan*/ **,int,int) ; 

void ff_mpv_reconstruct_mb(MpegEncContext *s, int16_t block[12][64])
{
#if !CONFIG_SMALL
    if(s->out_format == FMT_MPEG1) {
        if(s->avctx->lowres) mpv_reconstruct_mb_internal(s, block, 1, 1);
        else                 mpv_reconstruct_mb_internal(s, block, 0, 1);
    } else
#endif
    if(s->avctx->lowres) mpv_reconstruct_mb_internal(s, block, 1, 0);
    else                  mpv_reconstruct_mb_internal(s, block, 0, 0);
}