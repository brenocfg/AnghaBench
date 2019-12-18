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
typedef  int uint64_t ;
struct mips_option {char* desc; int flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 

__attribute__((used)) static void
dump_mips_option_flags(const char *name, struct mips_option *opt, uint64_t info)
{
	int first;

	first = 1;
	for (; opt->desc != NULL; opt++) {
		if (info & opt->flag) {
			printf(" %-10.10s %s\n", first ? name : "",
			    opt->desc);
			first = 0;
		}
	}
}