#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
typedef  int int16_t ;
struct TYPE_3__ {int predictor; int step; } ;
typedef  TYPE_1__ ADPCMChannelStatus ;

/* Variables and functions */
 void* av_clip (int,int,int) ; 

__attribute__((used)) static inline int16_t adpcm_agm_expand_nibble(ADPCMChannelStatus *c, int8_t nibble)
{
    int delta, pred, step, add;

    pred = c->predictor;
    delta = nibble & 7;
    step = c->step;
    add = (delta * 2 + 1) * step;
    if (add < 0)
        add = add + 7;

    if ((nibble & 8) == 0)
        pred = av_clip(pred + (add >> 3), -32767, 32767);
    else
        pred = av_clip(pred - (add >> 3), -32767, 32767);

    switch (delta) {
    case 7:
        step *= 0x99;
        break;
    case 6:
        c->step = av_clip(c->step * 2, 127, 24576);
        c->predictor = pred;
        return pred;
    case 5:
        step *= 0x66;
        break;
    case 4:
        step *= 0x4d;
        break;
    default:
        step *= 0x39;
        break;
    }

    if (step < 0)
        step += 0x3f;

    c->step = step >> 6;
    c->step = av_clip(c->step, 127, 24576);
    c->predictor = pred;
    return pred;
}