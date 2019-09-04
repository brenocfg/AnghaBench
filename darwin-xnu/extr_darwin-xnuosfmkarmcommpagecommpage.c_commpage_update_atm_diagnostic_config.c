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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ _COMM_PAGE_ATM_DIAGNOSTIC_CONFIG ; 
 scalar_t__ _COMM_PAGE_RW_OFFSET ; 
 scalar_t__ commPagePtr ; 

void
commpage_update_atm_diagnostic_config(uint32_t diagnostic_config)
{
	if (commPagePtr)
		*((volatile uint32_t*)(_COMM_PAGE_ATM_DIAGNOSTIC_CONFIG+_COMM_PAGE_RW_OFFSET)) = diagnostic_config;
}