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
 int /*<<< orphan*/  arcmsr_flush_hba_cache (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_flush_hbb_cache (struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  arcmsr_flush_hbc_cache (struct AdapterControlBlock*) ; 

__attribute__((used)) static void arcmsr_flush_adapter_cache(struct AdapterControlBlock *acb)
{
	switch (acb->adapter_type) {

	case ACB_ADAPTER_TYPE_A: {
		arcmsr_flush_hba_cache(acb);
		}
		break;

	case ACB_ADAPTER_TYPE_B: {
		arcmsr_flush_hbb_cache(acb);
		}
		break;
	case ACB_ADAPTER_TYPE_C: {
		arcmsr_flush_hbc_cache(acb);
		}
	}
}