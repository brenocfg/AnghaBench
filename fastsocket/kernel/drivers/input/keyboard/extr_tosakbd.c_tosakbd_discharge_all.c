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
 int /*<<< orphan*/  GPCR1 ; 
 int /*<<< orphan*/  GPCR2 ; 
 int /*<<< orphan*/  GPDR1 ; 
 int /*<<< orphan*/  GPDR2 ; 
 int /*<<< orphan*/  TOSA_GPIO_HIGH_STROBE_BIT ; 
 int /*<<< orphan*/  TOSA_GPIO_LOW_STROBE_BIT ; 

__attribute__((used)) static inline void tosakbd_discharge_all(void)
{
	/* STROBE All HiZ */
	GPCR1  = TOSA_GPIO_HIGH_STROBE_BIT;
	GPDR1 &= ~TOSA_GPIO_HIGH_STROBE_BIT;
	GPCR2  = TOSA_GPIO_LOW_STROBE_BIT;
	GPDR2 &= ~TOSA_GPIO_LOW_STROBE_BIT;
}