#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mfxPayload ;
struct TYPE_10__ {TYPE_2__* work_frames; } ;
struct TYPE_8__ {void* Payload; } ;
struct TYPE_9__ {int used; TYPE_1__ enc_ctrl; int /*<<< orphan*/  frame; struct TYPE_9__* next; } ;
typedef  TYPE_2__ QSVFrame ;
typedef  TYPE_3__ QSVEncContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int QSV_MAX_ENC_PAYLOAD ; 
 int /*<<< orphan*/  av_frame_alloc () ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 void* av_mallocz (int) ; 
 int /*<<< orphan*/  clear_unused_frames (TYPE_3__*) ; 

__attribute__((used)) static int get_free_frame(QSVEncContext *q, QSVFrame **f)
{
    QSVFrame *frame, **last;

    clear_unused_frames(q);

    frame = q->work_frames;
    last  = &q->work_frames;
    while (frame) {
        if (!frame->used) {
            *f = frame;
            frame->used = 1;
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
    frame->enc_ctrl.Payload = av_mallocz(sizeof(mfxPayload*) * QSV_MAX_ENC_PAYLOAD);
    if (!frame->enc_ctrl.Payload) {
        av_freep(&frame);
        return AVERROR(ENOMEM);
    }
    *last = frame;

    *f = frame;
    frame->used = 1;

    return 0;
}