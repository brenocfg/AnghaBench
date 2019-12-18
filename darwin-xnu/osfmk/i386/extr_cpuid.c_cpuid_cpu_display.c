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
struct TYPE_2__ {char* cpuid_brand_string; } ;

/* Variables and functions */
 TYPE_1__* cpuid_cpu_infop ; 
 int /*<<< orphan*/  kprintf (char*,char const*,char*) ; 

void
cpuid_cpu_display(
	const char	*header)
{
    if (cpuid_cpu_infop->cpuid_brand_string[0] != '\0') {
	kprintf("%s: %s\n", header, cpuid_cpu_infop->cpuid_brand_string);
    }
}