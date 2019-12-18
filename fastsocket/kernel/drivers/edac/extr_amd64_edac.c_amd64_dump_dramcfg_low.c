#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 int BIT (int) ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  debugf1 (char*,...) ; 

__attribute__((used)) static void amd64_dump_dramcfg_low(u32 dclr, int chan)
{
	debugf1("F2x%d90 (DRAM Cfg Low): 0x%08x\n", chan, dclr);

	debugf1("  DIMM type: %sbuffered; all DIMMs support ECC: %s\n",
		(dclr & BIT(16)) ?  "un" : "",
		(dclr & BIT(19)) ? "yes" : "no");

	debugf1("  PAR/ERR parity: %s\n",
		(dclr & BIT(8)) ?  "enabled" : "disabled");

	if (boot_cpu_data.x86 == 0x10)
		debugf1("  DCT 128bit mode width: %s\n",
			(dclr & BIT(11)) ?  "128b" : "64b");

	debugf1("  x4 logical DIMMs present: L0: %s L1: %s L2: %s L3: %s\n",
		(dclr & BIT(12)) ?  "yes" : "no",
		(dclr & BIT(13)) ?  "yes" : "no",
		(dclr & BIT(14)) ?  "yes" : "no",
		(dclr & BIT(15)) ?  "yes" : "no");
}