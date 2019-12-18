#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  cpuid_brand_string; int /*<<< orphan*/  cpuid_signature; int /*<<< orphan*/  cpuid_microcode_version; int /*<<< orphan*/  cpuid_stepping; int /*<<< orphan*/  cpuid_model; int /*<<< orphan*/  cpuid_family; } ;
typedef  TYPE_1__ i386_cpu_info_t ;

/* Variables and functions */
 TYPE_1__* cpuid_info () ; 
 int /*<<< orphan*/  paniclog_append_noflush (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
mca_report_cpu_info(void)
{
	i386_cpu_info_t *infop = cpuid_info();

	paniclog_append_noflush(" family: %d model: %d stepping: %d microcode: %d\n",
		infop->cpuid_family,
		infop->cpuid_model,
		infop->cpuid_stepping,
		infop->cpuid_microcode_version);
	paniclog_append_noflush(" signature: 0x%x\n",
		infop->cpuid_signature);
	paniclog_append_noflush(" %s\n",
		infop->cpuid_brand_string);

}