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
 float elu_gradient (float) ; 
 float hardtan_gradient (float) ; 
 float leaky_gradient (float) ; 
 float lhtan_gradient (float) ; 
 float linear_gradient (float) ; 
 float loggy_gradient (float) ; 
 float logistic_gradient (float) ; 
 float plse_gradient (float) ; 
 float ramp_gradient (float) ; 
 float relie_gradient (float) ; 
 float relu_gradient (float) ; 
 float selu_gradient (float) ; 
 float stair_gradient (float) ; 
 float tanh_gradient (float) ; 

float gradient(float x, ACTIVATION a)
{
    switch(a){
        case LINEAR:
            return linear_gradient(x);
        case LOGISTIC:
            return logistic_gradient(x);
        case LOGGY:
            return loggy_gradient(x);
        case RELU:
            return relu_gradient(x);
        case ELU:
            return elu_gradient(x);
        case SELU:
            return selu_gradient(x);
        case RELIE:
            return relie_gradient(x);
        case RAMP:
            return ramp_gradient(x);
        case LEAKY:
            return leaky_gradient(x);
        case TANH:
            return tanh_gradient(x);
        case PLSE:
            return plse_gradient(x);
        case STAIR:
            return stair_gradient(x);
        case HARDTAN:
            return hardtan_gradient(x);
        case LHTAN:
            return lhtan_gradient(x);
    }
    return 0;
}