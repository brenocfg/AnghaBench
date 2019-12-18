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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kgdb_nmicallback (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

__attribute__((used)) static int kgdb_call_nmi_hook(struct pt_regs *regs)
{
	kgdb_nmicallback(raw_smp_processor_id(), regs);
	return 0;
}