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
 int SRMMU_ET_MASK ; 
 int SRMMU_ET_PTE ; 
 int pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int srmmu_pte_present(pte_t pte)
{ return ((pte_val(pte) & SRMMU_ET_MASK) == SRMMU_ET_PTE); }