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
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {unsigned int nb_in; scalar_t__ frame_ready; TYPE_1__* in; } ;
struct TYPE_4__ {scalar_t__ pts_next; int /*<<< orphan*/ * frame; scalar_t__ have_next; scalar_t__ sync; } ;
typedef  TYPE_2__ FFFrameSync ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/ * av_frame_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int av_frame_make_writable (int /*<<< orphan*/ *) ; 

int ff_framesync_get_frame(FFFrameSync *fs, unsigned in, AVFrame **rframe,
                            unsigned get)
{
    AVFrame *frame;
    unsigned need_copy = 0, i;
    int64_t pts_next;
    int ret;

    if (!fs->in[in].frame) {
        *rframe = NULL;
        return 0;
    }
    frame = fs->in[in].frame;
    if (get) {
        /* Find out if we need to copy the frame: is there another sync
           stream, and do we know if its current frame will outlast this one? */
        pts_next = fs->in[in].have_next ? fs->in[in].pts_next : INT64_MAX;
        for (i = 0; i < fs->nb_in && !need_copy; i++)
            if (i != in && fs->in[i].sync &&
                (!fs->in[i].have_next || fs->in[i].pts_next < pts_next))
                need_copy = 1;
        if (need_copy) {
            if (!(frame = av_frame_clone(frame)))
                return AVERROR(ENOMEM);
            if ((ret = av_frame_make_writable(frame)) < 0) {
                av_frame_free(&frame);
                return ret;
            }
        } else {
            fs->in[in].frame = NULL;
        }
        fs->frame_ready = 0;
    }
    *rframe = frame;
    return 0;
}