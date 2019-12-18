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

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ idr_get_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_hba_index ; 

int
lpfc_get_instance(void)
{
	int instance = 0;

	/* Assign an unused number */
	if (!idr_pre_get(&lpfc_hba_index, GFP_KERNEL))
		return -1;
	if (idr_get_new(&lpfc_hba_index, NULL, &instance))
		return -1;
	return instance;
}