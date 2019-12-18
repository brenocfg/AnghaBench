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
struct TYPE_5__ {int /*<<< orphan*/ * dither; TYPE_1__* quantize; int /*<<< orphan*/ * prediction; int /*<<< orphan*/ * invert_quantize; } ;
struct TYPE_4__ {int /*<<< orphan*/  quantized_sample; } ;
typedef  TYPE_2__ Channel ;

/* Variables and functions */
 int NB_SUBBANDS ; 
 int /*<<< orphan*/  aptx_process_subband (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** tables ; 

__attribute__((used)) static void aptx_invert_quantize_and_prediction(Channel *channel, int hd)
{
    int subband;
    for (subband = 0; subband < NB_SUBBANDS; subband++)
        aptx_process_subband(&channel->invert_quantize[subband],
                             &channel->prediction[subband],
                             channel->quantize[subband].quantized_sample,
                             channel->dither[subband],
                             &tables[hd][subband]);
}