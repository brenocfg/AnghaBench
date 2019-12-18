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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __pte (int) ; 
 int page_to_pfn (struct page*) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static pte_t srmmu_mk_pte(struct page *page, pgprot_t pgprot)
{ return __pte((page_to_pfn(page) << (PAGE_SHIFT-4)) | pgprot_val(pgprot)); }