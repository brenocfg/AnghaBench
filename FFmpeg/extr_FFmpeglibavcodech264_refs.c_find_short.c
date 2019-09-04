#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int debug; } ;
struct TYPE_8__ {int short_ref_count; TYPE_5__* avctx; TYPE_1__** short_ref; } ;
struct TYPE_7__ {int frame_num; } ;
typedef  TYPE_1__ H264Picture ;
typedef  TYPE_2__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int FF_DEBUG_MMCO ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int,int,TYPE_1__*) ; 

__attribute__((used)) static H264Picture *find_short(H264Context *h, int frame_num, int *idx)
{
    int i;

    for (i = 0; i < h->short_ref_count; i++) {
        H264Picture *pic = h->short_ref[i];
        if (h->avctx->debug & FF_DEBUG_MMCO)
            av_log(h->avctx, AV_LOG_DEBUG, "%d %d %p\n", i, pic->frame_num, pic);
        if (pic->frame_num == frame_num) {
            *idx = i;
            return pic;
        }
    }
    return NULL;
}