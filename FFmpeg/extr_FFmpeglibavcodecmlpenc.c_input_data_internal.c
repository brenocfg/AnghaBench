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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_5__ {int* lossless_check_data; int frame_index; int num_substreams; int* inout_buffer; int* frame_size; int /*<<< orphan*/ * max_output_bits; TYPE_1__* restart_header; } ;
struct TYPE_4__ {unsigned int max_channel; } ;
typedef  TYPE_1__ RestartHeader ;
typedef  TYPE_2__ MLPEncodeContext ;

/* Variables and functions */
 scalar_t__ FFABS (int) ; 
 int /*<<< orphan*/  number_sbits (scalar_t__) ; 

__attribute__((used)) static void input_data_internal(MLPEncodeContext *ctx, const uint8_t *samples,
                                int is24)
{
    int32_t *lossless_check_data = ctx->lossless_check_data;
    const int32_t *samples_32 = (const int32_t *) samples;
    const int16_t *samples_16 = (const int16_t *) samples;
    unsigned int substr;

    lossless_check_data += ctx->frame_index * ctx->num_substreams;

    for (substr = 0; substr < ctx->num_substreams; substr++) {
        RestartHeader  *rh = &ctx->restart_header [substr];
        int32_t *sample_buffer = ctx->inout_buffer;
        int32_t temp_lossless_check_data = 0;
        uint32_t greatest = 0;
        unsigned int channel;
        int i;

        for (i = 0; i < ctx->frame_size[ctx->frame_index]; i++) {
            for (channel = 0; channel <= rh->max_channel; channel++) {
                uint32_t abs_sample;
                int32_t sample;

                sample = is24 ? *samples_32++ >> 8 : *samples_16++ << 8;

                /* TODO Find out if number_sbits can be used for negative values. */
                abs_sample = FFABS(sample);
                if (greatest < abs_sample)
                    greatest = abs_sample;

                temp_lossless_check_data ^= (sample & 0x00ffffff) << channel;
                *sample_buffer++ = sample;
            }

            sample_buffer += 2; /* noise channels */
        }

        ctx->max_output_bits[ctx->frame_index] = number_sbits(greatest);

        *lossless_check_data++ = temp_lossless_check_data;
    }
}