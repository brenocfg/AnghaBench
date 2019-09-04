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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  cpuid_extfeatures () ; 
 int /*<<< orphan*/  cpuid_get_extfeature_names (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kprintf (char*,char const*,int /*<<< orphan*/ ) ; 

void
cpuid_extfeature_display(
	const char	*header)
{
	char	buf[256];

	kprintf("%s: %s\n", header,
		  cpuid_get_extfeature_names(cpuid_extfeatures(),
						buf, sizeof(buf)));
}