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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  ppnum_t ;

/* Variables and functions */
 int /*<<< orphan*/  pmap_page_protect_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
pmap_page_protect(
	ppnum_t ppnum,
	vm_prot_t prot)
{
	pmap_page_protect_options(ppnum, prot, 0, NULL);
}