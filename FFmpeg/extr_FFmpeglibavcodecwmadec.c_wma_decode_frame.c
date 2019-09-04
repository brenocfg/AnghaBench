#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int frame_len; int /*<<< orphan*/ ** frame_out; TYPE_1__* avctx; scalar_t__ block_pos; scalar_t__ block_num; } ;
typedef  TYPE_2__ WMACodecContext ;
struct TYPE_5__ {int channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (float*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int wma_decode_block (TYPE_2__*) ; 

__attribute__((used)) static int wma_decode_frame(WMACodecContext *s, float **samples,
                            int samples_offset)
{
    int ret, ch;

#ifdef TRACE
    ff_tlog(s->avctx, "***decode_frame: %d size=%d\n",
            s->frame_count++, s->frame_len);
#endif /* TRACE */

    /* read each block */
    s->block_num = 0;
    s->block_pos = 0;
    for (;;) {
        ret = wma_decode_block(s);
        if (ret < 0)
            return -1;
        if (ret)
            break;
    }

    for (ch = 0; ch < s->avctx->channels; ch++) {
        /* copy current block to output */
        memcpy(samples[ch] + samples_offset, s->frame_out[ch],
               s->frame_len * sizeof(*s->frame_out[ch]));
        /* prepare for next block */
        memmove(&s->frame_out[ch][0], &s->frame_out[ch][s->frame_len],
                s->frame_len * sizeof(*s->frame_out[ch]));

#ifdef TRACE
        dump_floats(s, "samples", 6, samples[ch] + samples_offset,
                    s->frame_len);
#endif /* TRACE */
    }

    return 0;
}