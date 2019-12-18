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
 unsigned int pwm_cycles ; 
 int pwm_mult ; 

__attribute__((used)) static int convert_sample(unsigned int v)
{
  if (v == 0)
    return 0;
  if (v > pwm_cycles)
    v = pwm_cycles;
  return ((int)v - pwm_cycles / 2) * pwm_mult;
}