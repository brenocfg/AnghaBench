#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ compress_factor; int channels; scalar_t__ channels_coupled; scalar_t__ dc_correction; } ;
typedef  TYPE_1__ DynamicAudioNormalizerContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 scalar_t__ DBL_EPSILON ; 
 double const get_max_local_gain (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perform_compression (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perform_dc_correction (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_gain_history (TYPE_1__*,int,double const) ; 

__attribute__((used)) static void analyze_frame(DynamicAudioNormalizerContext *s, AVFrame *frame)
{
    if (s->dc_correction) {
        perform_dc_correction(s, frame);
    }

    if (s->compress_factor > DBL_EPSILON) {
        perform_compression(s, frame);
    }

    if (s->channels_coupled) {
        const double current_gain_factor = get_max_local_gain(s, frame, -1);
        int c;

        for (c = 0; c < s->channels; c++)
            update_gain_history(s, c, current_gain_factor);
    } else {
        int c;

        for (c = 0; c < s->channels; c++)
            update_gain_history(s, c, get_max_local_gain(s, frame, c));
    }
}