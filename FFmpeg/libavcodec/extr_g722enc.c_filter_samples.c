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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* apply_qmf ) (int /*<<< orphan*/ *,int*) ;} ;
struct TYPE_5__ {int prev_samples_pos; int /*<<< orphan*/ * prev_samples; TYPE_1__ dsp; } ;
typedef  TYPE_2__ G722Context ;

/* Variables and functions */
 int PREV_SAMPLES_BUF_SIZE ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static inline void filter_samples(G722Context *c, const int16_t *samples,
                                  int *xlow, int *xhigh)
{
    int xout[2];
    c->prev_samples[c->prev_samples_pos++] = samples[0];
    c->prev_samples[c->prev_samples_pos++] = samples[1];
    c->dsp.apply_qmf(c->prev_samples + c->prev_samples_pos - 24, xout);
    *xlow  = xout[0] + xout[1] >> 14;
    *xhigh = xout[0] - xout[1] >> 14;
    if (c->prev_samples_pos >= PREV_SAMPLES_BUF_SIZE) {
        memmove(c->prev_samples,
                c->prev_samples + c->prev_samples_pos - 22,
                22 * sizeof(c->prev_samples[0]));
        c->prev_samples_pos = 22;
    }
}