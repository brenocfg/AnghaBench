#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int re; int /*<<< orphan*/  im; } ;
struct TYPE_7__ {int /*<<< orphan*/  txi; int /*<<< orphan*/  (* txi_fn ) (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int) ;} ;
typedef  TYPE_1__ DenoiseState ;
typedef  TYPE_2__ AVComplexFloat ;

/* Variables and functions */
 int FREQ_SIZE ; 
 int WINDOW_SIZE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static void inverse_transform(DenoiseState *st, float *out, const AVComplexFloat *in)
{
    AVComplexFloat x[WINDOW_SIZE];
    AVComplexFloat y[WINDOW_SIZE];

    for (int i = 0; i < FREQ_SIZE; i++)
        x[i] = in[i];

    for (int i = FREQ_SIZE; i < WINDOW_SIZE; i++) {
        x[i].re =  x[WINDOW_SIZE - i].re;
        x[i].im = -x[WINDOW_SIZE - i].im;
    }

    st->txi_fn(st->txi, y, x, sizeof(float));

    for (int i = 0; i < WINDOW_SIZE; i++)
        out[i] = y[i].re / WINDOW_SIZE;
}