#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {void** extended_data; size_t nb_samples; int /*<<< orphan*/  format; } ;
struct TYPE_16__ {int /*<<< orphan*/ * samples; int /*<<< orphan*/ * overlap; } ;
struct TYPE_15__ {int channels; TYPE_5__* block; } ;
struct TYPE_13__ {int /*<<< orphan*/  framesize; } ;
struct TYPE_14__ {int /*<<< orphan*/  bufqueue; TYPE_2__ packet; TYPE_1__* avctx; } ;
struct TYPE_12__ {int frame_size; } ;
typedef  TYPE_3__ OpusEncContext ;
typedef  TYPE_4__ CeltFrame ;
typedef  TYPE_5__ CeltBlock ;
typedef  TYPE_6__ AVFrame ;

/* Variables and functions */
 size_t const FFMIN (int const,int const) ; 
 int const OPUS_BLOCK_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (TYPE_6__**) ; 
 void* av_get_bytes_per_sample (int /*<<< orphan*/ ) ; 
 TYPE_6__* ff_bufqueue_get (int /*<<< orphan*/ *) ; 
 TYPE_6__* ff_bufqueue_peek (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static void celt_frame_setup_input(OpusEncContext *s, CeltFrame *f)
{
    AVFrame *cur = NULL;
    const int subframesize = s->avctx->frame_size;
    int subframes = OPUS_BLOCK_SIZE(s->packet.framesize) / subframesize;

    cur = ff_bufqueue_get(&s->bufqueue);

    for (int ch = 0; ch < f->channels; ch++) {
        CeltBlock *b = &f->block[ch];
        const void *input = cur->extended_data[ch];
        size_t bps = av_get_bytes_per_sample(cur->format);
        memcpy(b->overlap, input, bps*cur->nb_samples);
    }

    av_frame_free(&cur);

    for (int sf = 0; sf < subframes; sf++) {
        if (sf != (subframes - 1))
            cur = ff_bufqueue_get(&s->bufqueue);
        else
            cur = ff_bufqueue_peek(&s->bufqueue, 0);

        for (int ch = 0; ch < f->channels; ch++) {
            CeltBlock *b = &f->block[ch];
            const void *input = cur->extended_data[ch];
            const size_t bps  = av_get_bytes_per_sample(cur->format);
            const size_t left = (subframesize - cur->nb_samples)*bps;
            const size_t len  = FFMIN(subframesize, cur->nb_samples)*bps;
            memcpy(&b->samples[sf*subframesize], input, len);
            memset(&b->samples[cur->nb_samples], 0, left);
        }

        /* Last frame isn't popped off and freed yet - we need it for overlap */
        if (sf != (subframes - 1))
            av_frame_free(&cur);
    }
}