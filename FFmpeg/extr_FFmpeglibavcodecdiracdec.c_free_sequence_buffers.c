#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__* data; } ;
struct TYPE_10__ {int /*<<< orphan*/  mcscratch; int /*<<< orphan*/  mctmp; int /*<<< orphan*/  edge_emu_buffer_base; int /*<<< orphan*/  blmotion; int /*<<< orphan*/  sbsplit; scalar_t__ buffer_stride; TYPE_3__* plane; int /*<<< orphan*/  delay_frames; int /*<<< orphan*/  ref_frames; TYPE_1__* all_frames; } ;
struct TYPE_8__ {int /*<<< orphan*/  tmp; int /*<<< orphan*/  buf_base; } ;
struct TYPE_9__ {TYPE_2__ idwt; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** hpel_base; int /*<<< orphan*/  interpolated; TYPE_6__* avframe; } ;
typedef  TYPE_4__ DiracContext ;

/* Variables and functions */
 int MAX_FRAMES ; 
 int /*<<< orphan*/  av_frame_unref (TYPE_6__*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void free_sequence_buffers(DiracContext *s)
{
    int i, j, k;

    for (i = 0; i < MAX_FRAMES; i++) {
        if (s->all_frames[i].avframe->data[0]) {
            av_frame_unref(s->all_frames[i].avframe);
            memset(s->all_frames[i].interpolated, 0, sizeof(s->all_frames[i].interpolated));
        }

        for (j = 0; j < 3; j++)
            for (k = 1; k < 4; k++)
                av_freep(&s->all_frames[i].hpel_base[j][k]);
    }

    memset(s->ref_frames, 0, sizeof(s->ref_frames));
    memset(s->delay_frames, 0, sizeof(s->delay_frames));

    for (i = 0; i < 3; i++) {
        av_freep(&s->plane[i].idwt.buf_base);
        av_freep(&s->plane[i].idwt.tmp);
    }

    s->buffer_stride = 0;
    av_freep(&s->sbsplit);
    av_freep(&s->blmotion);
    av_freep(&s->edge_emu_buffer_base);

    av_freep(&s->mctmp);
    av_freep(&s->mcscratch);
}