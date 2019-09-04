#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sample_mask ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {scalar_t__* shift; } ;
struct TYPE_9__ {scalar_t__* quant_step_size; TYPE_2__ matrix_params; } ;
struct TYPE_8__ {int number_of_samples; int /*<<< orphan*/ * sample_buffer; TYPE_1__* cur_restart_header; TYPE_4__* cur_decoding_params; } ;
struct TYPE_6__ {unsigned int max_channel; } ;
typedef  TYPE_1__ RestartHeader ;
typedef  TYPE_2__ MatrixParams ;
typedef  TYPE_3__ MLPEncodeContext ;
typedef  TYPE_4__ DecodingParams ;

/* Variables and functions */
 int MAX_CHANNELS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ number_trailing_zeroes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void determine_quant_step_size(MLPEncodeContext *ctx)
{
    DecodingParams *dp = ctx->cur_decoding_params;
    RestartHeader  *rh = ctx->cur_restart_header;
    MatrixParams *mp = &dp->matrix_params;
    int32_t *sample_buffer = ctx->sample_buffer;
    int32_t sample_mask[MAX_CHANNELS];
    unsigned int channel;
    int i;

    memset(sample_mask, 0x00, sizeof(sample_mask));

    for (i = 0; i < ctx->number_of_samples; i++) {
        for (channel = 0; channel <= rh->max_channel; channel++)
            sample_mask[channel] |= *sample_buffer++;

        sample_buffer += 2; /* noise channels */
    }

    for (channel = 0; channel <= rh->max_channel; channel++)
        dp->quant_step_size[channel] = number_trailing_zeroes(sample_mask[channel]) - mp->shift[channel];
}