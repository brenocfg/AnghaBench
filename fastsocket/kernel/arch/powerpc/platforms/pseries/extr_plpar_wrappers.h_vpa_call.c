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

/* Variables and functions */
 int /*<<< orphan*/  H_REGISTER_VPA ; 
 long plpar_hcall_norets (int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static inline long vpa_call(unsigned long flags, unsigned long cpu,
		unsigned long vpa)
{
	/* flags are in bits 16-18 (counting from most significant bit) */
	flags = flags << (63 - 18);

	return plpar_hcall_norets(H_REGISTER_VPA, flags, cpu, vpa);
}