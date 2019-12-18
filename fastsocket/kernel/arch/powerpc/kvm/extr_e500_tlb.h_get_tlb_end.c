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
typedef  scalar_t__ u64 ;
struct tlbe {int dummy; } ;
typedef  scalar_t__ gva_t ;

/* Variables and functions */
 scalar_t__ get_tlb_bytes (struct tlbe const*) ; 
 scalar_t__ get_tlb_eaddr (struct tlbe const*) ; 

__attribute__((used)) static inline gva_t get_tlb_end(const struct tlbe *tlbe)
{
	u64 bytes = get_tlb_bytes(tlbe);
	return get_tlb_eaddr(tlbe) + bytes - 1;
}