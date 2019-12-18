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
 scalar_t__ powf (float,int) ; 
 float sqrt (scalar_t__) ; 

__attribute__((used)) static float easing_out_circ(float t, float b, float c, float d)
{
   return(c * sqrt(1 - powf(t / d - 1, 2)) + b);
}