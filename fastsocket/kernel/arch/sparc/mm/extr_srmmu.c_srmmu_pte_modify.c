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
 int SRMMU_CHG_MASK ; 
 int /*<<< orphan*/  __pte (int) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 
 int pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline pte_t srmmu_pte_modify(pte_t pte, pgprot_t newprot)
{ return __pte((pte_val(pte) & SRMMU_CHG_MASK) | pgprot_val(newprot)); }