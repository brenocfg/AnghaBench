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
typedef  int uint8_t ;
typedef  int int16_t ;
struct TYPE_3__ {int step; int predictor; } ;
typedef  TYPE_1__ ADPCMChannelStatus ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int abs (int) ; 
 int av_clip (int,int,int) ; 
 int av_clip_int16 (int) ; 
 int* ff_adpcm_yamaha_difflookup ; 
 int* ff_adpcm_yamaha_indexscale ; 

__attribute__((used)) static inline uint8_t adpcm_yamaha_compress_sample(ADPCMChannelStatus *c,
                                                   int16_t sample)
{
    int nibble, delta;

    if (!c->step) {
        c->predictor = 0;
        c->step      = 127;
    }

    delta = sample - c->predictor;

    nibble = FFMIN(7, abs(delta) * 4 / c->step) + (delta < 0) * 8;

    c->predictor += ((c->step * ff_adpcm_yamaha_difflookup[nibble]) / 8);
    c->predictor = av_clip_int16(c->predictor);
    c->step = (c->step * ff_adpcm_yamaha_indexscale[nibble]) >> 8;
    c->step = av_clip(c->step, 127, 24576);

    return nibble;
}