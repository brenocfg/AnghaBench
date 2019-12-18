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
struct mm_struct {int /*<<< orphan*/ * pgd; } ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 unsigned long SRMMU_PGDIR_SHIFT ; 

__attribute__((used)) static inline pgd_t *srmmu_pgd_offset(struct mm_struct * mm, unsigned long address)
{ return mm->pgd + (address >> SRMMU_PGDIR_SHIFT); }