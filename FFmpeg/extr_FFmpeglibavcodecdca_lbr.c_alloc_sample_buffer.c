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
struct TYPE_3__ {int nchannels; int nsubbands; float* ts_buffer; float*** time_samples; int /*<<< orphan*/  ts_size; } ;
typedef  TYPE_1__ DCALbrDecoder ;

/* Variables and functions */
 int DCA_LBR_TIME_HISTORY ; 
 int DCA_LBR_TIME_SAMPLES ; 
 int /*<<< orphan*/  av_fast_mallocz (float**,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int alloc_sample_buffer(DCALbrDecoder *s)
{
    // Reserve space for history and padding
    int nchsamples = DCA_LBR_TIME_SAMPLES + DCA_LBR_TIME_HISTORY * 2;
    int nsamples = nchsamples * s->nchannels * s->nsubbands;
    int ch, sb;
    float *ptr;

    // Reallocate time sample buffer
    av_fast_mallocz(&s->ts_buffer, &s->ts_size, nsamples * sizeof(float));
    if (!s->ts_buffer)
        return -1;

    ptr = s->ts_buffer + DCA_LBR_TIME_HISTORY;
    for (ch = 0; ch < s->nchannels; ch++) {
        for (sb = 0; sb < s->nsubbands; sb++) {
            s->time_samples[ch][sb] = ptr;
            ptr += nchsamples;
        }
    }

    return 0;
}