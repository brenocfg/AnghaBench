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
struct TYPE_3__ {int nb_inputs; int* input_state; float* weights; float* scale_norm; int weight_sum; int dropout_transition; int sample_rate; float* input_scale; } ;
typedef  TYPE_1__ MixContext ;

/* Variables and functions */
 int FFMAX (int,float) ; 
 int INPUT_ON ; 

__attribute__((used)) static void calculate_scales(MixContext *s, int nb_samples)
{
    float weight_sum = 0.f;
    int i;

    for (i = 0; i < s->nb_inputs; i++)
        if (s->input_state[i] & INPUT_ON)
            weight_sum += s->weights[i];

    for (i = 0; i < s->nb_inputs; i++) {
        if (s->input_state[i] & INPUT_ON) {
            if (s->scale_norm[i] > weight_sum / s->weights[i]) {
                s->scale_norm[i] -= ((s->weight_sum / s->weights[i]) / s->nb_inputs) *
                                    nb_samples / (s->dropout_transition * s->sample_rate);
                s->scale_norm[i] = FFMAX(s->scale_norm[i], weight_sum / s->weights[i]);
            }
        }
    }

    for (i = 0; i < s->nb_inputs; i++) {
        if (s->input_state[i] & INPUT_ON)
            s->input_scale[i] = 1.0f / s->scale_norm[i];
        else
            s->input_scale[i] = 0.0f;
    }
}