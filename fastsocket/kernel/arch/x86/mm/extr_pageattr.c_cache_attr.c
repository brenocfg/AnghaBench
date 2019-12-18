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
 int _PAGE_PAT ; 
 int _PAGE_PAT_LARGE ; 
 int _PAGE_PCD ; 
 int _PAGE_PWT ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cache_attr(pgprot_t attr)
{
	return pgprot_val(attr) &
		(_PAGE_PAT | _PAGE_PAT_LARGE | _PAGE_PWT | _PAGE_PCD);
}