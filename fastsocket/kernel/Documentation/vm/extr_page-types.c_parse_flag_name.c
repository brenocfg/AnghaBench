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
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 unsigned long long BITS_COMPOUND ; 
 char** page_flag_names ; 
 unsigned long long parse_number (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static uint64_t parse_flag_name(const char *str, int len)
{
	int i;

	if (!*str || !len)
		return 0;

	if (len <= 8 && !strncmp(str, "compound", len))
		return BITS_COMPOUND;

	for (i = 0; i < ARRAY_SIZE(page_flag_names); i++) {
		if (!page_flag_names[i])
			continue;
		if (!strncmp(str, page_flag_names[i] + 2, len))
			return 1ULL << i;
	}

	return parse_number(str);
}