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
struct sram_list_struct {void const* addr; struct sram_list_struct* next; } ;
struct TYPE_3__ {struct sram_list_struct* sram_list; } ;
struct mm_struct {TYPE_1__ context; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 TYPE_2__* current ; 
 int /*<<< orphan*/  kfree (struct sram_list_struct*) ; 
 int /*<<< orphan*/  sram_free (void const*) ; 

int sram_free_with_lsl(const void *addr)
{
	struct sram_list_struct *lsl, **tmp;
	struct mm_struct *mm = current->mm;

	for (tmp = &mm->context.sram_list; *tmp; tmp = &(*tmp)->next)
		if ((*tmp)->addr == addr)
			goto found;
	return -1;
found:
	lsl = *tmp;
	sram_free(addr);
	*tmp = lsl->next;
	kfree(lsl);

	return 0;
}