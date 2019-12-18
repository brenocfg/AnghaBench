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
struct TYPE_3__ {int nb_inputs; int* input_state; int active_inputs; scalar_t__ duration_mode; } ;
typedef  TYPE_1__ MixContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 scalar_t__ DURATION_FIRST ; 
 scalar_t__ DURATION_SHORTEST ; 
 int INPUT_ON ; 

__attribute__((used)) static int calc_active_inputs(MixContext *s)
{
    int i;
    int active_inputs = 0;
    for (i = 0; i < s->nb_inputs; i++)
        active_inputs += !!(s->input_state[i] & INPUT_ON);
    s->active_inputs = active_inputs;

    if (!active_inputs ||
        (s->duration_mode == DURATION_FIRST && !(s->input_state[0] & INPUT_ON)) ||
        (s->duration_mode == DURATION_SHORTEST && active_inputs != s->nb_inputs))
        return AVERROR_EOF;
    return 0;
}