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
typedef  int /*<<< orphan*/  uint8_t ;
struct AdapterControlBlock {int adapter_type; } ;

/* Variables and functions */
#define  ACB_ADAPTER_TYPE_A 130 
#define  ACB_ADAPTER_TYPE_B 129 
#define  ACB_ADAPTER_TYPE_C 128 
 int /*<<< orphan*/  arcmsr_abort_hba_allcmd (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_abort_hbb_allcmd (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_abort_hbc_allcmd (struct AdapterControlBlock*) ; 

__attribute__((used)) static uint8_t arcmsr_abort_allcmd(struct AdapterControlBlock *acb)
{
	uint8_t rtnval = 0;
	switch (acb->adapter_type) {
	case ACB_ADAPTER_TYPE_A: {
		rtnval = arcmsr_abort_hba_allcmd(acb);
		}
		break;

	case ACB_ADAPTER_TYPE_B: {
		rtnval = arcmsr_abort_hbb_allcmd(acb);
		}
		break;

	case ACB_ADAPTER_TYPE_C: {
		rtnval = arcmsr_abort_hbc_allcmd(acb);
		}
	}
	return rtnval;
}