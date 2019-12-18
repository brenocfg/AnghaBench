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
 int /*<<< orphan*/  GEDR2 ; 
 int /*<<< orphan*/  GPDR1 ; 
 int /*<<< orphan*/  GPDR2 ; 
 int /*<<< orphan*/  GPSR1 ; 
 int /*<<< orphan*/  GPSR2 ; 
 int /*<<< orphan*/  KB_DISCHARGE_DELAY ; 
 int /*<<< orphan*/  TOSA_GPIO_ALL_SENSE_BIT ; 
 int /*<<< orphan*/  TOSA_GPIO_HIGH_STROBE_BIT ; 
 int /*<<< orphan*/  TOSA_GPIO_LOW_STROBE_BIT ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tosakbd_activate_all(void)
{
	/* STROBE ALL -> High */
	GPSR1  = TOSA_GPIO_HIGH_STROBE_BIT;
	GPDR1 |= TOSA_GPIO_HIGH_STROBE_BIT;
	GPSR2  = TOSA_GPIO_LOW_STROBE_BIT;
	GPDR2 |= TOSA_GPIO_LOW_STROBE_BIT;

	udelay(KB_DISCHARGE_DELAY);

	/* STATE CLEAR */
	GEDR2 |= TOSA_GPIO_ALL_SENSE_BIT;
}