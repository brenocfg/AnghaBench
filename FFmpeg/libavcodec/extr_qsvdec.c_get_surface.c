#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxFrameSurface1 ;
struct TYPE_10__ {TYPE_1__* work_frames; } ;
struct TYPE_9__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  frame; struct TYPE_9__* next; int /*<<< orphan*/  used; } ;
typedef  TYPE_1__ QSVFrame ;
typedef  TYPE_2__ QSVContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int alloc_frame (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_frame_alloc () ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  qsv_clear_unused_frames (TYPE_2__*) ; 

__attribute__((used)) static int get_surface(AVCodecContext *avctx, QSVContext *q, mfxFrameSurface1 **surf)
{
    QSVFrame *frame, **last;
    int ret;

    qsv_clear_unused_frames(q);

    frame = q->work_frames;
    last  = &q->work_frames;
    while (frame) {
        if (!frame->used) {
            ret = alloc_frame(avctx, q, frame);
            if (ret < 0)
                return ret;
            *surf = &frame->surface;
            return 0;
        }

        last  = &frame->next;
        frame = frame->next;
    }

    frame = av_mallocz(sizeof(*frame));
    if (!frame)
        return AVERROR(ENOMEM);
    frame->frame = av_frame_alloc();
    if (!frame->frame) {
        av_freep(&frame);
        return AVERROR(ENOMEM);
    }
    *last = frame;

    ret = alloc_frame(avctx, q, frame);
    if (ret < 0)
        return ret;

    *surf = &frame->surface;

    return 0;
}