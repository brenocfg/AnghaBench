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
struct TYPE_3__ {float r0; float r1; float k1; float cor0; float cor1; float var0; float var1; float x_est; } ;
typedef  TYPE_1__ PredictorState ;

/* Variables and functions */

__attribute__((used)) static inline void reset_predict_state(PredictorState *ps)
{
    ps->r0    = 0.0f;
    ps->r1    = 0.0f;
    ps->k1    = 0.0f;
    ps->cor0  = 0.0f;
    ps->cor1  = 0.0f;
    ps->var0  = 1.0f;
    ps->var1  = 1.0f;
    ps->x_est = 0.0f;
}