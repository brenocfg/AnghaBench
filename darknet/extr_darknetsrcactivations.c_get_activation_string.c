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

char *get_activation_string(ACTIVATION a)
{
    switch(a){
        case LOGISTIC:
            return "logistic";
        case LOGGY:
            return "loggy";
        case RELU:
            return "relu";
        case ELU:
            return "elu";
        case SELU:
            return "selu";
        case RELIE:
            return "relie";
        case RAMP:
            return "ramp";
        case LINEAR:
            return "linear";
        case TANH:
            return "tanh";
        case PLSE:
            return "plse";
        case LEAKY:
            return "leaky";
        case STAIR:
            return "stair";
        case HARDTAN:
            return "hardtan";
        case LHTAN:
            return "lhtan";
        default:
            break;
    }
    return "relu";
}