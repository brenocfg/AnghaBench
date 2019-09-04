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

/* Variables and functions */

__attribute__((used)) static float iir_filter(int in, float state[2])
{
    float ret;

    ret = 0.7548f * (in - state[0]) + 0.5095f * state[1];
    state[0] = in;
    state[1] = ret;
    return ret;
}