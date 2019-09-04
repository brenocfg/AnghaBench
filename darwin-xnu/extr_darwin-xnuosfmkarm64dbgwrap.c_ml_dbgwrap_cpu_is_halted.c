#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int dbgwrap_reg_t ;
struct TYPE_3__ {scalar_t__* coresight_base; } ;
typedef  TYPE_1__ cpu_data_t ;
typedef  int boolean_t ;

/* Variables and functions */
 size_t CORESIGHT_UTT ; 
 int volatile DBGWRAP_DBGACK ; 
 scalar_t__ DBGWRAP_REG_OFFSET ; 
 int FALSE ; 
 TYPE_1__* cpu_datap (int) ; 

boolean_t
ml_dbgwrap_cpu_is_halted(int cpu_index)
{
	cpu_data_t *cdp = cpu_datap(cpu_index);
	if ((cdp == NULL) || (cdp->coresight_base[CORESIGHT_UTT] == 0))
		return FALSE;

	return ((*(volatile dbgwrap_reg_t *)(cdp->coresight_base[CORESIGHT_UTT] + DBGWRAP_REG_OFFSET) & DBGWRAP_DBGACK) != 0);
}