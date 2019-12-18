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
typedef  int ACTIVATION ;

/* Variables and functions */
#define  ELU 141 
#define  HARDTAN 140 
#define  LEAKY 139 
#define  LHTAN 138 
#define  LINEAR 137 
#define  LOGGY 136 
#define  LOGISTIC 135 
#define  PLSE 134 
#define  RAMP 133 
#define  RELIE 132 
#define  RELU 131 
#define  SELU 130 
#define  STAIR 129 
#define  TANH 128 
 float elu_activate (float) ; 
 float hardtan_activate (float) ; 
 float leaky_activate (float) ; 
 float lhtan_activate (float) ; 
 float linear_activate (float) ; 
 float loggy_activate (float) ; 
 float logistic_activate (float) ; 
 float plse_activate (float) ; 
 float ramp_activate (float) ; 
 float relie_activate (float) ; 
 float relu_activate (float) ; 
 float selu_activate (float) ; 
 float stair_activate (float) ; 
 float tanh_activate (float) ; 

float activate(float x, ACTIVATION a)
{
    switch(a){
        case LINEAR:
            return linear_activate(x);
        case LOGISTIC:
            return logistic_activate(x);
        case LOGGY:
            return loggy_activate(x);
        case RELU:
            return relu_activate(x);
        case ELU:
            return elu_activate(x);
        case SELU:
            return selu_activate(x);
        case RELIE:
            return relie_activate(x);
        case RAMP:
            return ramp_activate(x);
        case LEAKY:
            return leaky_activate(x);
        case TANH:
            return tanh_activate(x);
        case PLSE:
            return plse_activate(x);
        case STAIR:
            return stair_activate(x);
        case HARDTAN:
            return hardtan_activate(x);
        case LHTAN:
            return lhtan_activate(x);
    }
    return 0;
}