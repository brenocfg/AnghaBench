#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t burn_in; float learning_rate; size_t power; int policy; int scale; size_t step; int num_steps; size_t* steps; float* scales; int gamma; float max_batches; } ;
typedef  TYPE_1__ network ;

/* Variables and functions */
#define  CONSTANT 134 
#define  EXP 133 
#define  POLY 132 
#define  RANDOM 131 
#define  SIG 130 
#define  STEP 129 
#define  STEPS 128 
 int /*<<< orphan*/  exp (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t get_current_batch (TYPE_1__*) ; 
 float pow (int,size_t) ; 
 int rand_uniform (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

float get_current_rate(network *net)
{
    size_t batch_num = get_current_batch(net);
    int i;
    float rate;
    if (batch_num < net->burn_in) return net->learning_rate * pow((float)batch_num / net->burn_in, net->power);
    switch (net->policy) {
        case CONSTANT:
            return net->learning_rate;
        case STEP:
            return net->learning_rate * pow(net->scale, batch_num/net->step);
        case STEPS:
            rate = net->learning_rate;
            for(i = 0; i < net->num_steps; ++i){
                if(net->steps[i] > batch_num) return rate;
                rate *= net->scales[i];
            }
            return rate;
        case EXP:
            return net->learning_rate * pow(net->gamma, batch_num);
        case POLY:
            return net->learning_rate * pow(1 - (float)batch_num / net->max_batches, net->power);
        case RANDOM:
            return net->learning_rate * pow(rand_uniform(0,1), net->power);
        case SIG:
            return net->learning_rate * (1./(1.+exp(net->gamma*(batch_num - net->step))));
        default:
            fprintf(stderr, "Policy is weird!\n");
            return net->learning_rate;
    }
}