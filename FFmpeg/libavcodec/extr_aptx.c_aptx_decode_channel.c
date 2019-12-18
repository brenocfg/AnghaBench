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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  qmf; TYPE_1__* prediction; } ;
struct TYPE_4__ {int /*<<< orphan*/  previous_reconstructed_sample; } ;
typedef  TYPE_2__ Channel ;

/* Variables and functions */
 int NB_SUBBANDS ; 
 int /*<<< orphan*/  aptx_qmf_tree_synthesis (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aptx_decode_channel(Channel *channel, int32_t samples[4])
{
    int32_t subband_samples[4];
    int subband;
    for (subband = 0; subband < NB_SUBBANDS; subband++)
        subband_samples[subband] = channel->prediction[subband].previous_reconstructed_sample;
    aptx_qmf_tree_synthesis(&channel->qmf, subband_samples, samples);
}