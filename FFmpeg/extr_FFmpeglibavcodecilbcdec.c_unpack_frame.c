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
struct TYPE_4__ {int* lsf; int start; int state_first; int ifm; int* cb_index; int* gain_index; int* idx; } ;
struct TYPE_5__ {int mode; int /*<<< orphan*/  gb; TYPE_1__ frame; } ;
typedef  TYPE_1__ ILBCFrame ;
typedef  TYPE_2__ ILBCContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int unpack_frame(ILBCContext *s)
{
    ILBCFrame *frame = &s->frame;
    GetBitContext *gb = &s->gb;
    int j;

    frame->lsf[0] = get_bits(gb, 6);
    frame->lsf[1] = get_bits(gb, 7);
    frame->lsf[2] = get_bits(gb, 7);

    if (s->mode == 20) {
        frame->start          = get_bits(gb, 2);
        frame->state_first    = get_bits1(gb);
        frame->ifm            = get_bits(gb, 6);
        frame->cb_index[0]    = get_bits(gb, 6) << 1;
        frame->gain_index[0]  = get_bits(gb, 2) << 3;
        frame->gain_index[1]  = get_bits1(gb) << 3;
        frame->cb_index[3]    = get_bits(gb, 7) << 1;
        frame->gain_index[3]  = get_bits1(gb) << 4;
        frame->gain_index[4]  = get_bits1(gb) << 3;
        frame->gain_index[6]  = get_bits1(gb) << 4;
    } else {
        frame->lsf[3]         = get_bits(gb, 6);
        frame->lsf[4]         = get_bits(gb, 7);
        frame->lsf[5]         = get_bits(gb, 7);
        frame->start          = get_bits(gb, 3);
        frame->state_first    = get_bits1(gb);
        frame->ifm            = get_bits(gb, 6);
        frame->cb_index[0]    = get_bits(gb, 4) << 3;
        frame->gain_index[0]  = get_bits1(gb) << 4;
        frame->gain_index[1]  = get_bits1(gb) << 3;
        frame->cb_index[3]    = get_bits(gb, 6) << 2;
        frame->gain_index[3]  = get_bits1(gb) << 4;
        frame->gain_index[4]  = get_bits1(gb) << 3;
    }

    for (j = 0; j < 48; j++)
        frame->idx[j] = get_bits1(gb) << 2;

    if (s->mode == 20) {
        for (; j < 57; j++)
            frame->idx[j] = get_bits1(gb) << 2;

        frame->gain_index[1] |= get_bits1(gb) << 2;
        frame->gain_index[3] |= get_bits(gb, 2) << 2;
        frame->gain_index[4] |= get_bits1(gb) << 2;
        frame->gain_index[6] |= get_bits1(gb) << 3;
        frame->gain_index[7]  = get_bits(gb, 2) << 2;
    } else {
        for (; j < 58; j++)
            frame->idx[j] = get_bits1(gb) << 2;

        frame->cb_index[0]    |= get_bits(gb, 2) << 1;
        frame->gain_index[0]  |= get_bits1(gb) << 3;
        frame->gain_index[1]  |= get_bits1(gb) << 2;
        frame->cb_index[3]    |= get_bits1(gb) << 1;
        frame->cb_index[6]     = get_bits1(gb) << 7;
        frame->cb_index[6]    |= get_bits(gb, 6) << 1;
        frame->cb_index[9]     = get_bits(gb, 7) << 1;
        frame->cb_index[12]    = get_bits(gb, 3) << 5;
        frame->cb_index[12]   |= get_bits(gb, 4) << 1;
        frame->gain_index[3]  |= get_bits(gb, 2) << 2;
        frame->gain_index[4]  |= get_bits(gb, 2) << 1;
        frame->gain_index[6]   = get_bits(gb, 2) << 3;
        frame->gain_index[7]   = get_bits(gb, 2) << 2;
        frame->gain_index[9]   = get_bits1(gb) << 4;
        frame->gain_index[10]  = get_bits1(gb) << 3;
        frame->gain_index[12]  = get_bits1(gb) << 4;
        frame->gain_index[13]  = get_bits1(gb) << 3;
    }

    for (j = 0; j < 56; j++)
        frame->idx[j] |= get_bits(gb, 2);

    if (s->mode == 20) {
        frame->idx[56]        |= get_bits(gb, 2);
        frame->cb_index[0]    |= get_bits1(gb);
        frame->cb_index[1]     = get_bits(gb, 7);
        frame->cb_index[2]     = get_bits(gb, 6) << 1;
        frame->cb_index[2]    |= get_bits1(gb);
        frame->gain_index[0]  |= get_bits(gb, 3);
        frame->gain_index[1]  |= get_bits(gb, 2);
        frame->gain_index[2]   = get_bits(gb, 3);
        frame->cb_index[3]    |= get_bits1(gb);
        frame->cb_index[4]     = get_bits(gb, 6) << 1;
        frame->cb_index[4]    |= get_bits1(gb);
        frame->cb_index[5]     = get_bits(gb, 7);
        frame->cb_index[6]     = get_bits(gb, 8);
        frame->cb_index[7]     = get_bits(gb, 8);
        frame->cb_index[8]     = get_bits(gb, 8);
        frame->gain_index[3]  |= get_bits(gb, 2);
        frame->gain_index[4]  |= get_bits(gb, 2);
        frame->gain_index[5]   = get_bits(gb, 3);
        frame->gain_index[6]  |= get_bits(gb, 3);
        frame->gain_index[7]  |= get_bits(gb, 2);
        frame->gain_index[8]   = get_bits(gb, 3);
    } else {
        frame->idx[56]        |= get_bits(gb, 2);
        frame->idx[57]        |= get_bits(gb, 2);
        frame->cb_index[0]    |= get_bits1(gb);
        frame->cb_index[1]     = get_bits(gb, 7);
        frame->cb_index[2]     = get_bits(gb, 4) << 3;
        frame->cb_index[2]    |= get_bits(gb, 3);
        frame->gain_index[0]  |= get_bits(gb, 3);
        frame->gain_index[1]  |= get_bits(gb, 2);
        frame->gain_index[2]   = get_bits(gb, 3);
        frame->cb_index[3]    |= get_bits1(gb);
        frame->cb_index[4]     = get_bits(gb, 4) << 3;
        frame->cb_index[4]    |= get_bits(gb, 3);
        frame->cb_index[5]     = get_bits(gb, 7);
        frame->cb_index[6]    |= get_bits1(gb);
        frame->cb_index[7]     = get_bits(gb, 5) << 3;
        frame->cb_index[7]    |= get_bits(gb, 3);
        frame->cb_index[8]     = get_bits(gb, 8);
        frame->cb_index[9]    |= get_bits1(gb);
        frame->cb_index[10]    = get_bits(gb, 4) << 4;
        frame->cb_index[10]   |= get_bits(gb, 4);
        frame->cb_index[11]    = get_bits(gb, 8);
        frame->cb_index[12]   |= get_bits1(gb);
        frame->cb_index[13]    = get_bits(gb, 3) << 5;
        frame->cb_index[13]   |= get_bits(gb, 5);
        frame->cb_index[14]    = get_bits(gb, 8);
        frame->gain_index[3]  |= get_bits(gb, 2);
        frame->gain_index[4]  |= get_bits1(gb);
        frame->gain_index[5]   = get_bits(gb, 3);
        frame->gain_index[6]  |= get_bits(gb, 3);
        frame->gain_index[7]  |= get_bits(gb, 2);
        frame->gain_index[8]   = get_bits(gb, 3);
        frame->gain_index[9]  |= get_bits(gb, 4);
        frame->gain_index[10] |= get_bits1(gb) << 2;
        frame->gain_index[10] |= get_bits(gb, 2);
        frame->gain_index[11]  = get_bits(gb, 3);
        frame->gain_index[12] |= get_bits(gb, 4);
        frame->gain_index[13] |= get_bits(gb, 3);
        frame->gain_index[14]  = get_bits(gb, 3);
    }

    return get_bits1(gb);
}