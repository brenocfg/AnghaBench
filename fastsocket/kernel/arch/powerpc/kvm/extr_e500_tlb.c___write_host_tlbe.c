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
struct tlbe {int /*<<< orphan*/  mas7; int /*<<< orphan*/  mas3; int /*<<< orphan*/  mas2; int /*<<< orphan*/  mas1; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_MAS1 ; 
 int /*<<< orphan*/  SPRN_MAS2 ; 
 int /*<<< orphan*/  SPRN_MAS3 ; 
 int /*<<< orphan*/  SPRN_MAS7 ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __write_host_tlbe(struct tlbe *stlbe)
{
	mtspr(SPRN_MAS1, stlbe->mas1);
	mtspr(SPRN_MAS2, stlbe->mas2);
	mtspr(SPRN_MAS3, stlbe->mas3);
	mtspr(SPRN_MAS7, stlbe->mas7);
	__asm__ __volatile__ ("tlbwe\n" : : );
}