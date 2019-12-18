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
struct be_mcc_wrb {unsigned long tag0; int /*<<< orphan*/  tag1; } ;

/* Variables and functions */
 int /*<<< orphan*/  upper_32_bits (unsigned long) ; 

__attribute__((used)) static inline void fill_wrb_tags(struct be_mcc_wrb *wrb,
				 unsigned long addr)
{
	wrb->tag0 = addr & 0xFFFFFFFF;
	wrb->tag1 = upper_32_bits(addr);
}