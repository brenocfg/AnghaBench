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
struct TYPE_4__ {int filter_size; double* prev_amplification_factor; int /*<<< orphan*/ * gain_history_minimum; int /*<<< orphan*/ * gain_history_smoothed; int /*<<< orphan*/ * gain_history_original; scalar_t__ alt_boundary_mode; } ;
typedef  TYPE_1__ DynamicAudioNormalizerContext ;

/* Variables and functions */
 double FFMIN (double,double) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 scalar_t__ cqueue_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cqueue_enqueue (int /*<<< orphan*/ ,double const) ; 
 double cqueue_peek (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cqueue_pop (int /*<<< orphan*/ ) ; 
 int const cqueue_size (int /*<<< orphan*/ ) ; 
 double gaussian_filter (TYPE_1__*,int /*<<< orphan*/ ) ; 
 double minimum_filter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_gain_history(DynamicAudioNormalizerContext *s, int channel,
                                double current_gain_factor)
{
    if (cqueue_empty(s->gain_history_original[channel]) ||
        cqueue_empty(s->gain_history_minimum[channel])) {
        const int pre_fill_size = s->filter_size / 2;
        const double initial_value = s->alt_boundary_mode ? current_gain_factor : 1.0;

        s->prev_amplification_factor[channel] = initial_value;

        while (cqueue_size(s->gain_history_original[channel]) < pre_fill_size) {
            cqueue_enqueue(s->gain_history_original[channel], initial_value);
        }
    }

    cqueue_enqueue(s->gain_history_original[channel], current_gain_factor);

    while (cqueue_size(s->gain_history_original[channel]) >= s->filter_size) {
        double minimum;
        av_assert0(cqueue_size(s->gain_history_original[channel]) == s->filter_size);

        if (cqueue_empty(s->gain_history_minimum[channel])) {
            const int pre_fill_size = s->filter_size / 2;
            double initial_value = s->alt_boundary_mode ? cqueue_peek(s->gain_history_original[channel], 0) : 1.0;
            int input = pre_fill_size;

            while (cqueue_size(s->gain_history_minimum[channel]) < pre_fill_size) {
                input++;
                initial_value = FFMIN(initial_value, cqueue_peek(s->gain_history_original[channel], input));
                cqueue_enqueue(s->gain_history_minimum[channel], initial_value);
            }
        }

        minimum = minimum_filter(s->gain_history_original[channel]);

        cqueue_enqueue(s->gain_history_minimum[channel], minimum);

        cqueue_pop(s->gain_history_original[channel]);
    }

    while (cqueue_size(s->gain_history_minimum[channel]) >= s->filter_size) {
        double smoothed;
        av_assert0(cqueue_size(s->gain_history_minimum[channel]) == s->filter_size);
        smoothed = gaussian_filter(s, s->gain_history_minimum[channel]);

        cqueue_enqueue(s->gain_history_smoothed[channel], smoothed);

        cqueue_pop(s->gain_history_minimum[channel]);
    }
}