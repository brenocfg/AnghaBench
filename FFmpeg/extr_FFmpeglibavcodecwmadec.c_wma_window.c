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
struct TYPE_5__ {float* output; scalar_t__ block_len_bits; scalar_t__ prev_block_len_bits; int block_len; int frame_len_bits; scalar_t__ next_block_len_bits; int /*<<< orphan*/ * windows; TYPE_1__* fdsp; } ;
typedef  TYPE_2__ WMACodecContext ;
struct TYPE_4__ {int /*<<< orphan*/  (* vector_fmul_reverse ) (float*,float*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* vector_fmul_add ) (float*,float*,int /*<<< orphan*/ ,float*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (float*,float*,int /*<<< orphan*/ ,float*,int) ; 
 int /*<<< orphan*/  stub2 (float*,float*,int /*<<< orphan*/ ,float*,int) ; 
 int /*<<< orphan*/  stub3 (float*,float*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (float*,float*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wma_window(WMACodecContext *s, float *out)
{
    float *in = s->output;
    int block_len, bsize, n;

    /* left part */
    if (s->block_len_bits <= s->prev_block_len_bits) {
        block_len = s->block_len;
        bsize     = s->frame_len_bits - s->block_len_bits;

        s->fdsp->vector_fmul_add(out, in, s->windows[bsize],
                                out, block_len);
    } else {
        block_len = 1 << s->prev_block_len_bits;
        n         = (s->block_len - block_len) / 2;
        bsize     = s->frame_len_bits - s->prev_block_len_bits;

        s->fdsp->vector_fmul_add(out + n, in + n, s->windows[bsize],
                                out + n, block_len);

        memcpy(out + n + block_len, in + n + block_len, n * sizeof(float));
    }

    out += s->block_len;
    in  += s->block_len;

    /* right part */
    if (s->block_len_bits <= s->next_block_len_bits) {
        block_len = s->block_len;
        bsize     = s->frame_len_bits - s->block_len_bits;

        s->fdsp->vector_fmul_reverse(out, in, s->windows[bsize], block_len);
    } else {
        block_len = 1 << s->next_block_len_bits;
        n         = (s->block_len - block_len) / 2;
        bsize     = s->frame_len_bits - s->next_block_len_bits;

        memcpy(out, in, n * sizeof(float));

        s->fdsp->vector_fmul_reverse(out + n, in + n, s->windows[bsize],
                                    block_len);

        memset(out + n + block_len, 0, n * sizeof(float));
    }
}