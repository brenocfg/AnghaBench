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
struct lpfc_hba {int hbq_in_use; int hbq_count; TYPE_1__* hbqs; } ;
struct TYPE_4__ {int /*<<< orphan*/  entry_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  entry_count; } ;

/* Variables and functions */
 TYPE_2__** lpfc_hbq_defs ; 
 int /*<<< orphan*/  lpfc_sli_hbqbuf_init_hbqs (struct lpfc_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_sli4_rb_setup(struct lpfc_hba *phba)
{
	phba->hbq_in_use = 1;
	phba->hbqs[0].entry_count = lpfc_hbq_defs[0]->entry_count;
	phba->hbq_count = 1;
	/* Initially populate or replenish the HBQs */
	lpfc_sli_hbqbuf_init_hbqs(phba, 0);
	return 0;
}