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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int _PAGE_PRESENT ; 
 int pte_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_pte(pte_t pte)
{
	/*
	 * Remember that get_user_pages_fast() took a reference to the page, in
	 * get_pfn()?  We have to put it back now.
	 */
	if (pte_flags(pte) & _PAGE_PRESENT)
		put_page(pte_page(pte));
}