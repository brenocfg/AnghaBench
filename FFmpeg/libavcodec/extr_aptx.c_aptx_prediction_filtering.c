#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_4__ {int predicted_sample; int* s_weight; int previous_reconstructed_sample; int* d_weight; int predicted_difference; } ;
typedef  TYPE_1__ Prediction ;

/* Variables and functions */
 int FFDIFFSIGN (int,int /*<<< orphan*/ ) ; 
 int FF_SIGNBIT (int) ; 
 int MUL64 (int,int) ; 
 int* aptx_reconstructed_differences_update (TYPE_1__*,int,int) ; 
 void* av_clip_intp2 (int,int) ; 
 int rshift32 (int,int) ; 

__attribute__((used)) static void aptx_prediction_filtering(Prediction *prediction,
                                      int32_t reconstructed_difference,
                                      int order)
{
    int32_t reconstructed_sample, predictor, srd0;
    int32_t *reconstructed_differences;
    int64_t predicted_difference = 0;
    int i;

    reconstructed_sample = av_clip_intp2(reconstructed_difference + prediction->predicted_sample, 23);
    predictor = av_clip_intp2((MUL64(prediction->s_weight[0], prediction->previous_reconstructed_sample)
                             + MUL64(prediction->s_weight[1], reconstructed_sample)) >> 22, 23);
    prediction->previous_reconstructed_sample = reconstructed_sample;

    reconstructed_differences = aptx_reconstructed_differences_update(prediction, reconstructed_difference, order);
    srd0 = FFDIFFSIGN(reconstructed_difference, 0) * (1 << 23);
    for (i = 0; i < order; i++) {
        int32_t srd = FF_SIGNBIT(reconstructed_differences[-i-1]) | 1;
        prediction->d_weight[i] -= rshift32(prediction->d_weight[i] - srd*srd0, 8);
        predicted_difference += MUL64(reconstructed_differences[-i], prediction->d_weight[i]);
    }

    prediction->predicted_difference = av_clip_intp2(predicted_difference >> 22, 23);
    prediction->predicted_sample = av_clip_intp2(predictor + prediction->predicted_difference, 23);
}