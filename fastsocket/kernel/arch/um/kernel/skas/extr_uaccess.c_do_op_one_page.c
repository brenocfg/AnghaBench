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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  jmp_buf ;
struct TYPE_3__ {int /*<<< orphan*/ * fault_catcher; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_UML_USERCOPY ; 
 unsigned long PAGE_MASK ; 
 int UML_SETJMP (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 
 scalar_t__ kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * maybe_map (unsigned long,int) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int stub1 (unsigned long,int,void*) ; 

__attribute__((used)) static int do_op_one_page(unsigned long addr, int len, int is_write,
		 int (*op)(unsigned long addr, int len, void *arg), void *arg)
{
	jmp_buf buf;
	struct page *page;
	pte_t *pte;
	int n, faulted;

	pte = maybe_map(addr, is_write);
	if (pte == NULL)
		return -1;

	page = pte_page(*pte);
	addr = (unsigned long) kmap_atomic(page, KM_UML_USERCOPY) +
		(addr & ~PAGE_MASK);

	current->thread.fault_catcher = &buf;

	faulted = UML_SETJMP(&buf);
	if (faulted == 0)
		n = (*op)(addr, len, arg);
	else
		n = -1;

	current->thread.fault_catcher = NULL;

	kunmap_atomic(page, KM_UML_USERCOPY);

	return n;
}