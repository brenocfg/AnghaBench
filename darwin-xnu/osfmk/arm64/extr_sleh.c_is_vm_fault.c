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
#define  FSC_ACCESS_FLAG_FAULT_L1 137 
#define  FSC_ACCESS_FLAG_FAULT_L2 136 
#define  FSC_ACCESS_FLAG_FAULT_L3 135 
#define  FSC_PERMISSION_FAULT_L1 134 
#define  FSC_PERMISSION_FAULT_L2 133 
#define  FSC_PERMISSION_FAULT_L3 132 
#define  FSC_TRANSLATION_FAULT_L0 131 
#define  FSC_TRANSLATION_FAULT_L1 130 
#define  FSC_TRANSLATION_FAULT_L2 129 
#define  FSC_TRANSLATION_FAULT_L3 128 
 int TRUE ; 

__attribute__((used)) static int
is_vm_fault(fault_status_t status)
{
	switch (status) {
	case FSC_TRANSLATION_FAULT_L0:
	case FSC_TRANSLATION_FAULT_L1:
	case FSC_TRANSLATION_FAULT_L2:
	case FSC_TRANSLATION_FAULT_L3:
	case FSC_ACCESS_FLAG_FAULT_L1:
	case FSC_ACCESS_FLAG_FAULT_L2:
	case FSC_ACCESS_FLAG_FAULT_L3:
	case FSC_PERMISSION_FAULT_L1:
	case FSC_PERMISSION_FAULT_L2:
	case FSC_PERMISSION_FAULT_L3:
		return TRUE;
	default:
		return FALSE;
	}
}