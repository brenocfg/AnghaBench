#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int debug; } ;
struct TYPE_7__ {int /*<<< orphan*/  short_ref_count; TYPE_6__* avctx; } ;
typedef  int /*<<< orphan*/  H264Picture ;
typedef  TYPE_1__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int FF_DEBUG_MMCO ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_short (TYPE_1__*,int,int*) ; 
 int /*<<< orphan*/  remove_short_at_index (TYPE_1__*,int) ; 
 scalar_t__ unreference_pic (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static H264Picture *remove_short(H264Context *h, int frame_num, int ref_mask)
{
    H264Picture *pic;
    int i;

    if (h->avctx->debug & FF_DEBUG_MMCO)
        av_log(h->avctx, AV_LOG_DEBUG, "remove short %d count %d\n", frame_num, h->short_ref_count);

    pic = find_short(h, frame_num, &i);
    if (pic) {
        if (unreference_pic(h, pic, ref_mask))
            remove_short_at_index(h, i);
    }

    return pic;
}