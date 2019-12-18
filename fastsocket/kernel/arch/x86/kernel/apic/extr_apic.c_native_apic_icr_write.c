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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_ICR ; 
 int /*<<< orphan*/  APIC_ICR2 ; 
 int /*<<< orphan*/  SET_APIC_DEST_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void native_apic_icr_write(u32 low, u32 id)
{
	apic_write(APIC_ICR2, SET_APIC_DEST_FIELD(id));
	apic_write(APIC_ICR, low);
}