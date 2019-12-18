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
 int CO_APIC_IDE0 ; 
 char VISWS_320 ; 

__attribute__((used)) static inline int co_apic_ide0_hack(void)
{
	extern char visws_board_type;
	extern char visws_board_rev;

	if (visws_board_type == VISWS_320 && visws_board_rev == 5)
		return 5;
	return CO_APIC_IDE0;
}