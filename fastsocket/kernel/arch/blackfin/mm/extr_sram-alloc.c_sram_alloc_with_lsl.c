#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sram_list_struct {size_t length; struct sram_list_struct* next; void* addr; } ;
struct TYPE_3__ {struct sram_list_struct* sram_list; } ;
struct mm_struct {TYPE_1__ context; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long L1_DATA_A_SRAM ; 
 unsigned long L1_DATA_B_SRAM ; 
 unsigned long L1_INST_SRAM ; 
 unsigned long L2_SRAM ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  kfree (struct sram_list_struct*) ; 
 struct sram_list_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* l1_data_A_sram_alloc (size_t) ; 
 void* l1_data_B_sram_alloc (size_t) ; 
 void* l1_inst_sram_alloc (size_t) ; 
 void* l2_sram_alloc (size_t) ; 

void *sram_alloc_with_lsl(size_t size, unsigned long flags)
{
	void *addr = NULL;
	struct sram_list_struct *lsl = NULL;
	struct mm_struct *mm = current->mm;

	lsl = kzalloc(sizeof(struct sram_list_struct), GFP_KERNEL);
	if (!lsl)
		return NULL;

	if (flags & L1_INST_SRAM)
		addr = l1_inst_sram_alloc(size);

	if (addr == NULL && (flags & L1_DATA_A_SRAM))
		addr = l1_data_A_sram_alloc(size);

	if (addr == NULL && (flags & L1_DATA_B_SRAM))
		addr = l1_data_B_sram_alloc(size);

	if (addr == NULL && (flags & L2_SRAM))
		addr = l2_sram_alloc(size);

	if (addr == NULL) {
		kfree(lsl);
		return NULL;
	}
	lsl->addr = addr;
	lsl->length = size;
	lsl->next = mm->context.sram_list;
	mm->context.sram_list = lsl;
	return addr;
}