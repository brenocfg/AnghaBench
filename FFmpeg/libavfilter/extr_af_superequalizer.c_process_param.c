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
struct TYPE_3__ {float lower; float upper; float gain; } ;
typedef  TYPE_1__ EqParameter ;

/* Variables and functions */
 int NBANDS ; 
 float* bands ; 

__attribute__((used)) static void process_param(float *bc, EqParameter *param, float fs)
{
    int i;

    for (i = 0; i <= NBANDS; i++) {
        param[i].lower = i == 0 ? 0 : bands[i - 1];
        param[i].upper = i == NBANDS ? fs : bands[i];
        param[i].gain  = bc[i];
    }
}