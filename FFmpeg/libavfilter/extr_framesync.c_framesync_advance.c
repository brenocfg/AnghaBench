#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_7__ {int frame_ready; unsigned int nb_in; scalar_t__ sync_level; scalar_t__ pts; TYPE_1__* in; scalar_t__ eof; } ;
struct TYPE_6__ {scalar_t__ pts_next; scalar_t__ before; scalar_t__ state; scalar_t__ pts; scalar_t__ sync; scalar_t__ after; int /*<<< orphan*/ * frame; scalar_t__ have_next; int /*<<< orphan*/ * frame_next; } ;
typedef  TYPE_2__ FFFrameSync ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ EXT_INFINITY ; 
 scalar_t__ EXT_STOP ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ STATE_BOF ; 
 scalar_t__ STATE_EOF ; 
 scalar_t__ STATE_RUN ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int consume_from_fifos (TYPE_2__*) ; 
 int /*<<< orphan*/  framesync_eof (TYPE_2__*) ; 

__attribute__((used)) static int framesync_advance(FFFrameSync *fs)
{
    unsigned i;
    int64_t pts;
    int ret;

    while (!(fs->frame_ready || fs->eof)) {
        ret = consume_from_fifos(fs);
        if (ret <= 0)
            return ret;

        pts = INT64_MAX;
        for (i = 0; i < fs->nb_in; i++)
            if (fs->in[i].have_next && fs->in[i].pts_next < pts)
                pts = fs->in[i].pts_next;
        if (pts == INT64_MAX) {
            framesync_eof(fs);
            break;
        }
        for (i = 0; i < fs->nb_in; i++) {
            if (fs->in[i].pts_next == pts ||
                (fs->in[i].before == EXT_INFINITY &&
                 fs->in[i].state == STATE_BOF)) {
                av_frame_free(&fs->in[i].frame);
                fs->in[i].frame      = fs->in[i].frame_next;
                fs->in[i].pts        = fs->in[i].pts_next;
                fs->in[i].frame_next = NULL;
                fs->in[i].pts_next   = AV_NOPTS_VALUE;
                fs->in[i].have_next  = 0;
                fs->in[i].state      = fs->in[i].frame ? STATE_RUN : STATE_EOF;
                if (fs->in[i].sync == fs->sync_level && fs->in[i].frame)
                    fs->frame_ready = 1;
                if (fs->in[i].state == STATE_EOF &&
                    fs->in[i].after == EXT_STOP)
                    framesync_eof(fs);
            }
        }
        if (fs->frame_ready)
            for (i = 0; i < fs->nb_in; i++)
                if ((fs->in[i].state == STATE_BOF &&
                     fs->in[i].before == EXT_STOP))
                    fs->frame_ready = 0;
        fs->pts = pts;
    }
    return 0;
}