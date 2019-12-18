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
struct kvmppc_44x_tlbe {int word1; } ;

/* Variables and functions */

__attribute__((used)) static inline u64 get_tlb_raddr(const struct kvmppc_44x_tlbe *tlbe)
{
	u64 word1 = tlbe->word1;
	return ((word1 & 0xf) << 32) | (word1 & 0xfffffc00);
}