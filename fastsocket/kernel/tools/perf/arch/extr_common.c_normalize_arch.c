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
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static const char *normalize_arch(char *arch)
{
	if (!strcmp(arch, "x86_64"))
		return "x86";
	if (arch[0] == 'i' && arch[2] == '8' && arch[3] == '6')
		return "x86";
	if (!strcmp(arch, "sun4u") || !strncmp(arch, "sparc", 5))
		return "sparc";
	if (!strncmp(arch, "arm", 3) || !strcmp(arch, "sa110"))
		return "arm";
	if (!strncmp(arch, "s390", 4))
		return "s390";
	if (!strncmp(arch, "parisc", 6))
		return "parisc";
	if (!strncmp(arch, "powerpc", 7) || !strncmp(arch, "ppc", 3))
		return "powerpc";
	if (!strncmp(arch, "mips", 4))
		return "mips";
	if (!strncmp(arch, "sh", 2) && isdigit(arch[2]))
		return "sh";

	return arch;
}