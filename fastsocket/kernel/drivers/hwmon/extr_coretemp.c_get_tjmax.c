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
typedef  int u32 ;
struct device {int dummy; } ;
struct cpuinfo_x86 {int x86_model; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_TEMPERATURE_TARGET ; 
 int adjust_tjmax (struct cpuinfo_x86*,int,struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int rdmsr_safe_on_cpu (int,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int get_tjmax(struct cpuinfo_x86 *c, u32 id, struct device *dev)
{
	/* The 100C is default for both mobile and non mobile CPUs */
	int err;
	u32 eax, edx;
	u32 val;

	/*
	 * A new feature of current Intel(R) processors, the
	 * IA32_TEMPERATURE_TARGET contains the TjMax value
	 */
	err = rdmsr_safe_on_cpu(id, MSR_IA32_TEMPERATURE_TARGET, &eax, &edx);
	if (err) {
		dev_warn(dev, "Unable to read TjMax from CPU.\n");
	} else {
		val = (eax >> 16) & 0xff;
		/*
		 * If the TjMax is not plausible, an assumption
		 * will be used
		 */
		if (val > 80 && val < 120) {
			dev_info(dev, "TjMax is %d C.\n", val);
			return val * 1000;
		}
	}

	/*
	 * An assumption is made for early CPUs and unreadable MSR.
	 * NOTE: the given value may not be correct.
	 */

	switch (c->x86_model) {
	case 0xe:
	case 0xf:
	case 0x16:
	case 0x1a:
		dev_warn(dev, "TjMax is assumed as 100 C!\n");
		return 100000;
		break;
	case 0x17:
	case 0x1c:		/* Atom CPUs */
		return adjust_tjmax(c, id, dev);
		break;
	default:
		dev_warn(dev, "CPU (model=0x%x) is not supported yet,"
			" using default TjMax of 100C.\n", c->x86_model);
		return 100000;
	}
}