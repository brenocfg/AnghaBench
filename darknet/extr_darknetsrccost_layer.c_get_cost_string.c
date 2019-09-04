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
typedef  int COST_TYPE ;

/* Variables and functions */
#define  L1 133 
#define  MASKED 132 
#define  SEG 131 
#define  SMOOTH 130 
#define  SSE 129 
#define  WGAN 128 

char *get_cost_string(COST_TYPE a)
{
    switch(a){
        case SEG:
            return "seg";
        case SSE:
            return "sse";
        case MASKED:
            return "masked";
        case SMOOTH:
            return "smooth";
        case L1:
            return "L1";
        case WGAN:
            return "wgan";
    }
    return "sse";
}