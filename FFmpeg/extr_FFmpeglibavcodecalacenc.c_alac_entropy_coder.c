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
typedef  int int32_t ;
struct TYPE_5__ {unsigned int initial_history; int history_mult; } ;
struct TYPE_6__ {int** predictor_buf; int frame_size; int write_sample_size; TYPE_1__ rc; } ;
typedef  TYPE_2__ AlacEncodeContext ;

/* Variables and functions */
 int av_log2 (unsigned int) ; 
 int /*<<< orphan*/  encode_scalar (TYPE_2__*,unsigned int,int,int) ; 

__attribute__((used)) static void alac_entropy_coder(AlacEncodeContext *s, int ch)
{
    unsigned int history = s->rc.initial_history;
    int sign_modifier = 0, i, k;
    int32_t *samples = s->predictor_buf[ch];

    for (i = 0; i < s->frame_size;) {
        int x;

        k = av_log2((history >> 9) + 3);

        x  = -2 * (*samples) -1;
        x ^= x >> 31;

        samples++;
        i++;

        encode_scalar(s, x - sign_modifier, k, s->write_sample_size);

        history += x * s->rc.history_mult -
                   ((history * s->rc.history_mult) >> 9);

        sign_modifier = 0;
        if (x > 0xFFFF)
            history = 0xFFFF;

        if (history < 128 && i < s->frame_size) {
            unsigned int block_size = 0;

            k = 7 - av_log2(history) + ((history + 16) >> 6);

            while (*samples == 0 && i < s->frame_size) {
                samples++;
                i++;
                block_size++;
            }
            encode_scalar(s, block_size, k, 16);
            sign_modifier = (block_size <= 0xFFFF);
            history = 0;
        }

    }
}