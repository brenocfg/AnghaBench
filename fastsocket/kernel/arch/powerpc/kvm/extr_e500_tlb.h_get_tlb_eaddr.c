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
struct tlbe {int mas2; } ;
typedef  int gva_t ;

/* Variables and functions */

__attribute__((used)) static inline gva_t get_tlb_eaddr(const struct tlbe *tlbe)
{
	return tlbe->mas2 & 0xfffff000;
}