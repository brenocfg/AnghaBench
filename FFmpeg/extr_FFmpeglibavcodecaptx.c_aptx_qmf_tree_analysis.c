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
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * inner_filter_signal; int /*<<< orphan*/  outer_filter_signal; } ;
typedef  TYPE_1__ QMFAnalysis ;

/* Variables and functions */
 int /*<<< orphan*/  aptx_qmf_inner_coeffs ; 
 int /*<<< orphan*/  aptx_qmf_outer_coeffs ; 
 int /*<<< orphan*/  aptx_qmf_polyphase_analysis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aptx_qmf_tree_analysis(QMFAnalysis *qmf,
                                   int32_t samples[4],
                                   int32_t subband_samples[4])
{
    int32_t intermediate_samples[4];
    int i;

    /* Split 4 input samples into 2 intermediate subbands downsampled to 2 samples */
    for (i = 0; i < 2; i++)
        aptx_qmf_polyphase_analysis(qmf->outer_filter_signal,
                                    aptx_qmf_outer_coeffs, 23,
                                    &samples[2*i],
                                    &intermediate_samples[0+i],
                                    &intermediate_samples[2+i]);

    /* Split 2 intermediate subband samples into 4 final subbands downsampled to 1 sample */
    for (i = 0; i < 2; i++)
        aptx_qmf_polyphase_analysis(qmf->inner_filter_signal[i],
                                    aptx_qmf_inner_coeffs, 23,
                                    &intermediate_samples[2*i],
                                    &subband_samples[2*i+0],
                                    &subband_samples[2*i+1]);
}