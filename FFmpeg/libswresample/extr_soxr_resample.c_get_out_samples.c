#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct SwrContext {double in_sample_rate; scalar_t__ delayed_samples_fixup; scalar_t__ flushed; scalar_t__ resample; scalar_t__ out_sample_rate; } ;
typedef  int /*<<< orphan*/  soxr_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 double soxr_delay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t get_out_samples(struct SwrContext *s, int in_samples){
    double out_samples = (double)s->out_sample_rate / s->in_sample_rate * in_samples;
    double delayed_samples = soxr_delay((soxr_t)s->resample);

    if (s->flushed)
        delayed_samples += s->delayed_samples_fixup;

    return (int64_t)(out_samples + delayed_samples + 1 + .5);
}