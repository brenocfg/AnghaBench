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
typedef  int u64 ;
struct tlbe {int mas7; int mas3; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 get_tlb_raddr(const struct tlbe *tlbe)
{
	u64 rpn = tlbe->mas7;
	return (rpn << 32) | (tlbe->mas3 & 0xfffff000);
}