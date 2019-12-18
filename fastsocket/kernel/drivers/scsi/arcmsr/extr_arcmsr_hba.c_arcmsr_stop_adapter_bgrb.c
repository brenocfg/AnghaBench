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
struct AdapterControlBlock {int adapter_type; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 130 
#define  ACB_ADAPTER_TYPE_B 129 
#define  ACB_ADAPTER_TYPE_C 128 
 int /*<<< orphan*/  arcmsr_stop_hba_bgrb (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_stop_hbb_bgrb (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_stop_hbc_bgrb (struct AdapterControlBlock*) ; 

__attribute__((used)) static void arcmsr_stop_adapter_bgrb(struct AdapterControlBlock *acb)
{
	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A: {
		arcmsr_stop_hba_bgrb(acb);
		}
		break;

	case ACB_ADAPTER_TYPE_B: {
		arcmsr_stop_hbb_bgrb(acb);
		}
		break;
	case ACB_ADAPTER_TYPE_C: {
		arcmsr_stop_hbc_bgrb(acb);
		}
	}
}