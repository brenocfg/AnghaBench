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
typedef  int fault_status_t ;

/* Variables and functions */
 int FALSE ; 
#define  FSC_ASYNC_PARITY 132 
#define  FSC_SYNC_PARITY 131 
#define  FSC_SYNC_PARITY_TT_L1 130 
#define  FSC_SYNC_PARITY_TT_L2 129 
#define  FSC_SYNC_PARITY_TT_L3 128 
 int TRUE ; 

__attribute__((used)) static int
is_parity_error(fault_status_t status)
{
	switch (status) {
	case FSC_SYNC_PARITY:
	case FSC_ASYNC_PARITY:
	case FSC_SYNC_PARITY_TT_L1:
	case FSC_SYNC_PARITY_TT_L2:
	case FSC_SYNC_PARITY_TT_L3:
		return TRUE;
	default:
		return FALSE;
	}
}