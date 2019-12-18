#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float re; scalar_t__ im; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx; int /*<<< orphan*/  (* tx_fn ) (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int) ;} ;
typedef  TYPE_1__ DenoiseState ;
typedef  TYPE_2__ AVComplexFloat ;

/* Variables and functions */
 int /*<<< orphan*/  FREQ_SIZE ; 
 int /*<<< orphan*/  RNN_COPY (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int WINDOW_SIZE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static void forward_transform(DenoiseState *st, AVComplexFloat *out, const float *in)
{
    AVComplexFloat x[WINDOW_SIZE];
    AVComplexFloat y[WINDOW_SIZE];

    for (int i = 0; i < WINDOW_SIZE; i++) {
        x[i].re = in[i];
        x[i].im = 0;
    }

    st->tx_fn(st->tx, y, x, sizeof(float));

    RNN_COPY(out, y, FREQ_SIZE);
}