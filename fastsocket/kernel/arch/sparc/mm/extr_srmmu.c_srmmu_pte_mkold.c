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
 int SRMMU_REF ; 
 int /*<<< orphan*/  __pte (int) ; 
 int pte_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline pte_t srmmu_pte_mkold(pte_t pte)
{ return __pte(pte_val(pte) & ~SRMMU_REF);}