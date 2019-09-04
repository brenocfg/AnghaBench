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
 int /*<<< orphan*/  ERROR_STATUS ; 
 int LAPIC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LAPIC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lapic_esr_read(void)
{
	/* write-read register */
	LAPIC_WRITE(ERROR_STATUS, 0);
	return LAPIC_READ(ERROR_STATUS);
}