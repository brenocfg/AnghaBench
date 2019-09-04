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
typedef  int int16_t ;
struct TYPE_3__ {int sample1; int coeff1; int sample2; int coeff2; int idelta; } ;
typedef  TYPE_1__ ADPCMChannelStatus ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int INT_MAX ; 
 int av_clip_int16 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int* ff_adpcm_AdaptationTable ; 

__attribute__((used)) static inline int16_t adpcm_ms_expand_nibble(ADPCMChannelStatus *c, int nibble)
{
    int predictor;

    predictor = (((c->sample1) * (c->coeff1)) + ((c->sample2) * (c->coeff2))) / 64;
    predictor += ((nibble & 0x08)?(nibble - 0x10):(nibble)) * c->idelta;

    c->sample2 = c->sample1;
    c->sample1 = av_clip_int16(predictor);
    c->idelta = (ff_adpcm_AdaptationTable[(int)nibble] * c->idelta) >> 8;
    if (c->idelta < 16) c->idelta = 16;
    if (c->idelta > INT_MAX/768) {
        av_log(NULL, AV_LOG_WARNING, "idelta overflow\n");
        c->idelta = INT_MAX/768;
    }

    return c->sample1;
}