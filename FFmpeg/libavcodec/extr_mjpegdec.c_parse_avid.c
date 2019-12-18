#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_5__ {int debug; } ;
struct TYPE_4__ {int buggy_avid; int interlace_polarity; TYPE_3__* avctx; } ;
typedef  TYPE_1__ MJpegDecodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int FF_DEBUG_PICT_INFO ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static void parse_avid(MJpegDecodeContext *s, uint8_t *buf, int len)
{
    s->buggy_avid = 1;
    if (len > 14 && buf[12] == 1) /* 1 - NTSC */
        s->interlace_polarity = 1;
    if (len > 14 && buf[12] == 2) /* 2 - PAL */
        s->interlace_polarity = 0;
    if (s->avctx->debug & FF_DEBUG_PICT_INFO)
        av_log(s->avctx, AV_LOG_INFO, "AVID: len:%d %d\n", len, len > 14 ? buf[12] : -1);
}