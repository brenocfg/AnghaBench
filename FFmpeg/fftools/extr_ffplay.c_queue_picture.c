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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {int /*<<< orphan*/  pictq; } ;
typedef  TYPE_1__ VideoState ;
struct TYPE_10__ {int /*<<< orphan*/  format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  pict_type; } ;
struct TYPE_9__ {double pts; double duration; int serial; int /*<<< orphan*/  frame; int /*<<< orphan*/  sar; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pos; int /*<<< orphan*/  format; scalar_t__ uploaded; } ;
typedef  TYPE_2__ Frame ;
typedef  TYPE_3__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_move_ref (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int av_get_picture_type_char (int /*<<< orphan*/ ) ; 
 TYPE_2__* frame_queue_peek_writable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_queue_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,double) ; 
 int /*<<< orphan*/  set_default_window_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int queue_picture(VideoState *is, AVFrame *src_frame, double pts, double duration, int64_t pos, int serial)
{
    Frame *vp;

#if defined(DEBUG_SYNC)
    printf("frame_type=%c pts=%0.3f\n",
           av_get_picture_type_char(src_frame->pict_type), pts);
#endif

    if (!(vp = frame_queue_peek_writable(&is->pictq)))
        return -1;

    vp->sar = src_frame->sample_aspect_ratio;
    vp->uploaded = 0;

    vp->width = src_frame->width;
    vp->height = src_frame->height;
    vp->format = src_frame->format;

    vp->pts = pts;
    vp->duration = duration;
    vp->pos = pos;
    vp->serial = serial;

    set_default_window_size(vp->width, vp->height, vp->sar);

    av_frame_move_ref(vp->frame, src_frame);
    frame_queue_push(&is->pictq);
    return 0;
}