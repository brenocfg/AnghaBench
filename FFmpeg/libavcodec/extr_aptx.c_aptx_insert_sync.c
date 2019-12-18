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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_6__ {TYPE_1__* quantize; } ;
struct TYPE_5__ {scalar_t__ error; int /*<<< orphan*/  quantized_sample_parity_change; int /*<<< orphan*/  quantized_sample; } ;
typedef  TYPE_1__ Quantize ;
typedef  TYPE_2__ Channel ;

/* Variables and functions */
 int NB_CHANNELS ; 
 int NB_SUBBANDS ; 
 scalar_t__ aptx_check_parity (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aptx_insert_sync(Channel channels[NB_CHANNELS], int32_t *idx)
{
    if (aptx_check_parity(channels, idx)) {
        int i;
        Channel *c;
        static const int map[] = { 1, 2, 0, 3 };
        Quantize *min = &channels[NB_CHANNELS-1].quantize[map[0]];
        for (c = &channels[NB_CHANNELS-1]; c >= channels; c--)
            for (i = 0; i < NB_SUBBANDS; i++)
                if (c->quantize[map[i]].error < min->error)
                    min = &c->quantize[map[i]];

        /* Forcing the desired parity is done by offsetting by 1 the quantized
         * sample from the subband featuring the smallest quantization error. */
        min->quantized_sample = min->quantized_sample_parity_change;
    }
}