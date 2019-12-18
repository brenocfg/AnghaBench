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
 int /*<<< orphan*/  CORGI_GPIO_ALL_STROBE_BIT ; 
 int /*<<< orphan*/  GPCR2 ; 
 int /*<<< orphan*/  GPDR2 ; 

__attribute__((used)) static inline void corgikbd_discharge_all(void)
{
	/* STROBE All HiZ */
	GPCR2  = CORGI_GPIO_ALL_STROBE_BIT;
	GPDR2 &= ~CORGI_GPIO_ALL_STROBE_BIT;
}