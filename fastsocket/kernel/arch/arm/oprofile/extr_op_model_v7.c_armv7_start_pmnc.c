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
 int PMNC_E ; 
 int armv7_pmnc_read () ; 
 int /*<<< orphan*/  armv7_pmnc_write (int) ; 

__attribute__((used)) static inline void armv7_start_pmnc(void)
{
	armv7_pmnc_write(armv7_pmnc_read() | PMNC_E);
}