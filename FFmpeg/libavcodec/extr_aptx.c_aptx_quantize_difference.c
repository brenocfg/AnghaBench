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
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_6__ {int* quantize_intervals; int* quantize_dither_factors; int /*<<< orphan*/  tables_size; } ;
struct TYPE_5__ {int quantized_sample; int quantized_sample_parity_change; void* error; } ;
typedef  TYPE_1__ Quantize ;
typedef  TYPE_2__ ConstTables ;

/* Variables and functions */
 void* FFABS (int) ; 
 int FFMIN (int,int) ; 
 int MUL64 (int,int) ; 
 int /*<<< orphan*/  MULH (int,int) ; 
 int aptx_bin_search (int,int,int const*,int /*<<< orphan*/ ) ; 
 scalar_t__ av_clip_intp2 (int,int) ; 
 int rshift32_clip24 (int /*<<< orphan*/ ,int) ; 
 int rshift64 (int,int) ; 
 int rshift64_clip24 (int,int) ; 

__attribute__((used)) static void aptx_quantize_difference(Quantize *quantize,
                                     int32_t sample_difference,
                                     int32_t dither,
                                     int32_t quantization_factor,
                                     ConstTables *tables)
{
    const int32_t *intervals = tables->quantize_intervals;
    int32_t quantized_sample, dithered_sample, parity_change;
    int32_t d, mean, interval, inv, sample_difference_abs;
    int64_t error;

    sample_difference_abs = FFABS(sample_difference);
    sample_difference_abs = FFMIN(sample_difference_abs, (1 << 23) - 1);

    quantized_sample = aptx_bin_search(sample_difference_abs >> 4,
                                       quantization_factor,
                                       intervals, tables->tables_size);

    d = rshift32_clip24(MULH(dither, dither), 7) - (1 << 23);
    d = rshift64(MUL64(d, tables->quantize_dither_factors[quantized_sample]), 23);

    intervals += quantized_sample;
    mean = (intervals[1] + intervals[0]) / 2;
    interval = (intervals[1] - intervals[0]) * (-(sample_difference < 0) | 1);

    dithered_sample = rshift64_clip24(MUL64(dither, interval) + ((int64_t)av_clip_intp2(mean + d, 23) << 32), 32);
    error = ((int64_t)sample_difference_abs << 20) - MUL64(dithered_sample, quantization_factor);
    quantize->error = FFABS(rshift64(error, 23));

    parity_change = quantized_sample;
    if (error < 0)
        quantized_sample--;
    else
        parity_change--;

    inv = -(sample_difference < 0);
    quantize->quantized_sample               = quantized_sample ^ inv;
    quantize->quantized_sample_parity_change = parity_change    ^ inv;
}