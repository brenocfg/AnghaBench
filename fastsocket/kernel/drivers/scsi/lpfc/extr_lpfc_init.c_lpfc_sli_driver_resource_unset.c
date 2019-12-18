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
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_mem_free_all (struct lpfc_hba*) ; 

__attribute__((used)) static void
lpfc_sli_driver_resource_unset(struct lpfc_hba *phba)
{
	/* Free device driver memory allocated */
	lpfc_mem_free_all(phba);

	return;
}