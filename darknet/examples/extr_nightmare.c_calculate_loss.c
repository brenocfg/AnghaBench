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
 float mean_array (float*,int) ; 
 float sqrt (float) ; 
 float variance_array (float*,int) ; 

void calculate_loss(float *output, float *delta, int n, float thresh)
{
    int i;
    float mean = mean_array(output, n); 
    float var = variance_array(output, n);
    for(i = 0; i < n; ++i){
        if(delta[i] > mean + thresh*sqrt(var)) delta[i] = output[i];
        else delta[i] = 0;
    }
}