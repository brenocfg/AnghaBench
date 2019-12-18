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
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int PTRS_PER_PGD ; 
 int PTRS_PER_PMD ; 
 int USER_PTRS_PER_PGD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pgd_list_add (void*) ; 
 int /*<<< orphan*/  pgd_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ swapper_pg_dir ; 

void pgd_ctor(void *pgd)
{
	unsigned long flags;

	if (PTRS_PER_PMD == 1)
		spin_lock_irqsave(&pgd_lock, flags);

	memcpy((pgd_t *)pgd + USER_PTRS_PER_PGD,
			swapper_pg_dir + USER_PTRS_PER_PGD,
			(PTRS_PER_PGD - USER_PTRS_PER_PGD) * sizeof(pgd_t));

	if (PTRS_PER_PMD > 1)
		return;

	pgd_list_add(pgd);
	spin_unlock_irqrestore(&pgd_lock, flags);
	memset(pgd, 0, USER_PTRS_PER_PGD * sizeof(pgd_t));
}