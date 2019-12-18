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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ICR ; 
 int /*<<< orphan*/  ICRD ; 
 int LAPIC_ICRD_DEST_SHIFT ; 
 int* LAPIC_MMIO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
legacy_write_icr(uint32_t dst, uint32_t cmd)
{
	*LAPIC_MMIO(ICRD) = dst << LAPIC_ICRD_DEST_SHIFT;
	*LAPIC_MMIO(ICR) = cmd;
}