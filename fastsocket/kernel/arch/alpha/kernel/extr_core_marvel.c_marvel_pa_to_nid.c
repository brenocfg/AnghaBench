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
 int marvel_cpuid_to_nid (int) ; 

int
marvel_pa_to_nid(unsigned long pa)
{
	int cpuid;

	if ((pa >> 43) & 1) 	/* I/O */ 
		cpuid = (~(pa >> 35) & 0xff);
	else			/* mem */
		cpuid = ((pa >> 34) & 0x3) | ((pa >> (37 - 2)) & (0x1f << 2));

	return marvel_cpuid_to_nid(cpuid);
}