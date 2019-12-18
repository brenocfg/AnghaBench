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
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ cpu_has_apic ; 
 int /*<<< orphan*/  disable_apic ; 

__attribute__((used)) static u32 native_apic_read_dummy(u32 reg)
{
	WARN_ON_ONCE((cpu_has_apic && !disable_apic));
	return 0;
}