#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct adv_dvc_var {TYPE_1__* carr_freelist; TYPE_1__* carrier_buf; } ;
struct TYPE_5__ {void* next_vpa; void* carr_va; void* carr_pa; } ;
typedef  scalar_t__ ADV_SDCNT ;
typedef  void* ADV_PADDR ;
typedef  TYPE_1__ ADV_CARR_T ;

/* Variables and functions */
 scalar_t__ ADV_16BALIGN (TYPE_1__*) ; 
 scalar_t__ ADV_CARRIER_BUFSIZE ; 
 int /*<<< orphan*/  ADV_VADDR_TO_U32 (TYPE_1__*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_bus (TYPE_1__*) ; 

__attribute__((used)) static void AdvBuildCarrierFreelist(struct adv_dvc_var *asc_dvc)
{
	ADV_CARR_T *carrp;
	ADV_SDCNT buf_size;
	ADV_PADDR carr_paddr;

	carrp = (ADV_CARR_T *) ADV_16BALIGN(asc_dvc->carrier_buf);
	asc_dvc->carr_freelist = NULL;
	if (carrp == asc_dvc->carrier_buf) {
		buf_size = ADV_CARRIER_BUFSIZE;
	} else {
		buf_size = ADV_CARRIER_BUFSIZE - sizeof(ADV_CARR_T);
	}

	do {
		/* Get physical address of the carrier 'carrp'. */
		carr_paddr = cpu_to_le32(virt_to_bus(carrp));

		buf_size -= sizeof(ADV_CARR_T);

		carrp->carr_pa = carr_paddr;
		carrp->carr_va = cpu_to_le32(ADV_VADDR_TO_U32(carrp));

		/*
		 * Insert the carrier at the beginning of the freelist.
		 */
		carrp->next_vpa =
			cpu_to_le32(ADV_VADDR_TO_U32(asc_dvc->carr_freelist));
		asc_dvc->carr_freelist = carrp;

		carrp++;
	} while (buf_size > 0);
}