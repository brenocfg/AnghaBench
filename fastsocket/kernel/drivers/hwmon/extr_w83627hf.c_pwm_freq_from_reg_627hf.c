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
typedef  unsigned long u8 ;

/* Variables and functions */
 unsigned long W83627HF_BASE_PWM_FREQ ; 

__attribute__((used)) static inline unsigned long pwm_freq_from_reg_627hf(u8 reg)
{
	unsigned long freq;
	freq = W83627HF_BASE_PWM_FREQ >> reg;
	return freq;
}