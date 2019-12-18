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
struct kvm_pt_regs {int /*<<< orphan*/  cr_ipsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_PSR_ED ; 

__attribute__((used)) static inline void handle_lds(struct kvm_pt_regs *regs)
{
	regs->cr_ipsr |= IA64_PSR_ED;
}