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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int _PAGE_CACHE_WC ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 scalar_t__ pat_enabled ; 
 int /*<<< orphan*/  pgprot_noncached (int /*<<< orphan*/ ) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 

pgprot_t pgprot_writecombine(pgprot_t prot)
{
	if (pat_enabled)
		return __pgprot(pgprot_val(prot) | _PAGE_CACHE_WC);
	else
		return pgprot_noncached(prot);
}