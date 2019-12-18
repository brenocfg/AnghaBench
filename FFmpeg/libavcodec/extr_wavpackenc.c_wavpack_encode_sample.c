#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  WvChannel ;
struct TYPE_7__ {int holding_zero; int zeros_acc; int holding_one; int pend_data; int pend_count; TYPE_1__* c; } ;
typedef  TYPE_2__ WavPackWords ;
struct TYPE_8__ {TYPE_2__ w; int /*<<< orphan*/  pb; } ;
typedef  TYPE_3__ WavPackEncodeContext ;
struct TYPE_6__ {int* median; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (int*) ; 
 int /*<<< orphan*/  DEC_MED (int) ; 
 int GET_MED (int) ; 
 int /*<<< orphan*/  INC_MED (int) ; 
 int count_bits (int) ; 
 int /*<<< orphan*/  encode_flush (TYPE_3__*) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wavpack_encode_sample(WavPackEncodeContext *s, WvChannel *c, int32_t sample)
{
    WavPackWords *w = &s->w;
    uint32_t ones_count, low, high;
    int sign = sample < 0;

    if (s->w.c[0].median[0] < 2 && !s->w.holding_zero && s->w.c[1].median[0] < 2) {
        if (w->zeros_acc) {
            if (sample)
                encode_flush(s);
            else {
                w->zeros_acc++;
                return;
            }
        } else if (sample) {
            put_bits(&s->pb, 1, 0);
        } else {
            CLEAR(s->w.c[0].median);
            CLEAR(s->w.c[1].median);
            w->zeros_acc = 1;
            return;
        }
    }

    if (sign)
        sample = ~sample;

    if (sample < (int32_t) GET_MED(0)) {
        ones_count = low = 0;
        high = GET_MED(0) - 1;
        DEC_MED(0);
    } else {
        low = GET_MED(0);
        INC_MED(0);

        if (sample - low < GET_MED(1)) {
            ones_count = 1;
            high = low + GET_MED(1) - 1;
            DEC_MED(1);
        } else {
            low += GET_MED(1);
            INC_MED(1);

            if (sample - low < GET_MED(2)) {
                ones_count = 2;
                high = low + GET_MED(2) - 1;
                DEC_MED(2);
            } else {
                ones_count = 2 + (sample - low) / GET_MED(2);
                low += (ones_count - 2) * GET_MED(2);
                high = low + GET_MED(2) - 1;
                INC_MED(2);
            }
        }
    }

    if (w->holding_zero) {
        if (ones_count)
            w->holding_one++;

        encode_flush(s);

        if (ones_count) {
            w->holding_zero = 1;
            ones_count--;
        } else
            w->holding_zero = 0;
    } else
        w->holding_zero = 1;

    w->holding_one = ones_count * 2;

    if (high != low) {
        uint32_t maxcode = high - low, code = sample - low;
        int bitcount = count_bits(maxcode);
        uint32_t extras = (1 << bitcount) - maxcode - 1;

        if (code < extras) {
            w->pend_data |= code << w->pend_count;
            w->pend_count += bitcount - 1;
        } else {
            w->pend_data |= ((code + extras) >> 1) << w->pend_count;
            w->pend_count += bitcount - 1;
            w->pend_data |= ((code + extras) & 1) << w->pend_count++;
        }
    }

    w->pend_data |= ((int32_t) sign << w->pend_count++);

    if (!w->holding_zero)
        encode_flush(s);
}