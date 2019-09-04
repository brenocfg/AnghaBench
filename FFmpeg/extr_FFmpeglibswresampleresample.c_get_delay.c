#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct SwrContext {int in_buffer_count; int in_sample_rate; TYPE_1__* resample; } ;
typedef  int int64_t ;
struct TYPE_2__ {int filter_length; int phase_count; int src_incr; scalar_t__ frac; scalar_t__ index; } ;
typedef  TYPE_1__ ResampleContext ;

/* Variables and functions */
 int av_rescale (int,int,int) ; 

__attribute__((used)) static int64_t get_delay(struct SwrContext *s, int64_t base){
    ResampleContext *c = s->resample;
    int64_t num = s->in_buffer_count - (c->filter_length-1)/2;
    num *= c->phase_count;
    num -= c->index;
    num *= c->src_incr;
    num -= c->frac;
    return av_rescale(num, base, s->in_sample_rate*(int64_t)c->src_incr * c->phase_count);
}