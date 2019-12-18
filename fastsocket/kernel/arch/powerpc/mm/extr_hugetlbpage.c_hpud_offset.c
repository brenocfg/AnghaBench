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
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 scalar_t__ PUD_SHIFT ; 
 scalar_t__ huge_page_shift (struct hstate*) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static pud_t *hpud_offset(pgd_t *pgd, unsigned long addr, struct hstate *hstate)
{
	if (huge_page_shift(hstate) < PUD_SHIFT)
		return pud_offset(pgd, addr);
	else
		return (pud_t *) pgd;
}