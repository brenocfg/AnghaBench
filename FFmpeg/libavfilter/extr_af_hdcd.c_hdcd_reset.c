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
typedef  unsigned int uint64_t ;
struct TYPE_3__ {int readahead; unsigned int sustain_reset; int count_sustain_expired; unsigned int rate; scalar_t__ _ana_snb; scalar_t__ max_gain; scalar_t__* gain_counts; scalar_t__ count_transient_filter; scalar_t__ count_peak_extend; scalar_t__ code_counterC_unmatched; scalar_t__ code_counterC; scalar_t__ code_counterB_checkfails; scalar_t__ code_counterB; scalar_t__ code_counterA_almost; scalar_t__ code_counterA; scalar_t__ sustain; scalar_t__ running_gain; scalar_t__ control; scalar_t__ arg; scalar_t__ window; } ;
typedef  TYPE_1__ hdcd_state ;

/* Variables and functions */

__attribute__((used)) static void hdcd_reset(hdcd_state *state, unsigned rate, unsigned cdt_ms)
{
    int i;
    uint64_t sustain_reset = (uint64_t)cdt_ms * rate / 1000;

    state->window = 0;
    state->readahead = 32;
    state->arg = 0;
    state->control = 0;
    state->running_gain = 0;
    state->sustain_reset = sustain_reset;
    state->sustain = 0;

    state->code_counterA = 0;
    state->code_counterA_almost = 0;
    state->code_counterB = 0;
    state->code_counterB_checkfails = 0;
    state->code_counterC = 0;
    state->code_counterC_unmatched = 0;
    state->count_peak_extend = 0;
    state->count_transient_filter = 0;
    for(i = 0; i < 16; i++) state->gain_counts[i] = 0;
    state->max_gain = 0;
    state->count_sustain_expired = -1;

    state->rate = rate;
    state->_ana_snb = 0;
}