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
struct kvmppc_44x_tlbe {int dummy; } ;
typedef  int gva_t ;

/* Variables and functions */
 unsigned int get_tlb_size (struct kvmppc_44x_tlbe const*) ; 

__attribute__((used)) static inline gva_t get_tlb_bytes(const struct kvmppc_44x_tlbe *tlbe)
{
	unsigned int pgsize = get_tlb_size(tlbe);
	return 1 << 10 << (pgsize << 1);
}