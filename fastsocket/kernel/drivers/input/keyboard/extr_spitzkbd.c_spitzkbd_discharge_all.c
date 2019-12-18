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
 int /*<<< orphan*/  GPCR0 ; 
 int /*<<< orphan*/  GPCR1 ; 
 int /*<<< orphan*/  GPCR2 ; 
 int /*<<< orphan*/  GPCR3 ; 
 int /*<<< orphan*/  GPDR0 ; 
 int /*<<< orphan*/  GPDR1 ; 
 int /*<<< orphan*/  GPDR2 ; 
 int /*<<< orphan*/  GPDR3 ; 
 int /*<<< orphan*/  SPITZ_GPIO_G0_STROBE_BIT ; 
 int /*<<< orphan*/  SPITZ_GPIO_G1_STROBE_BIT ; 
 int /*<<< orphan*/  SPITZ_GPIO_G2_STROBE_BIT ; 
 int /*<<< orphan*/  SPITZ_GPIO_G3_STROBE_BIT ; 

__attribute__((used)) static inline void spitzkbd_discharge_all(void)
{
	/* STROBE All HiZ */
	GPCR0  =  SPITZ_GPIO_G0_STROBE_BIT;
	GPDR0 &= ~SPITZ_GPIO_G0_STROBE_BIT;
	GPCR1  =  SPITZ_GPIO_G1_STROBE_BIT;
	GPDR1 &= ~SPITZ_GPIO_G1_STROBE_BIT;
	GPCR2  =  SPITZ_GPIO_G2_STROBE_BIT;
	GPDR2 &= ~SPITZ_GPIO_G2_STROBE_BIT;
	GPCR3  =  SPITZ_GPIO_G3_STROBE_BIT;
	GPDR3 &= ~SPITZ_GPIO_G3_STROBE_BIT;
}