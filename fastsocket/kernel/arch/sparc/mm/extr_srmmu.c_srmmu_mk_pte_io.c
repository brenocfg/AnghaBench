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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  __pte (unsigned long) ; 
 unsigned long pgprot_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static pte_t srmmu_mk_pte_io(unsigned long page, pgprot_t pgprot, int space)
{ return __pte(((page) >> 4) | (space << 28) | pgprot_val(pgprot)); }