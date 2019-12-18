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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  page_flag_longname (scalar_t__) ; 
 int /*<<< orphan*/  page_flag_name (scalar_t__) ; 
 scalar_t__ parse_flag_names (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void describe_flags(const char *optarg)
{
	uint64_t flags = parse_flag_names(optarg, 0);

	printf("0x%016llx\t%s\t%s\n",
		(unsigned long long)flags,
		page_flag_name(flags),
		page_flag_longname(flags));
}