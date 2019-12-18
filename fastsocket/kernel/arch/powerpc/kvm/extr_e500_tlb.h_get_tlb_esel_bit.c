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
struct kvmppc_vcpu_e500 {int mas0; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int get_tlb_esel_bit(
		const struct kvmppc_vcpu_e500 *vcpu_e500)
{
	return (vcpu_e500->mas0 >> 16) & 0xfff;
}