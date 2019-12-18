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
 int tomoyo_file_matches_to_pattern2 (char const*,char const*,char const*,char const*) ; 

__attribute__((used)) static bool tomoyo_file_matches_to_pattern(const char *filename,
					   const char *filename_end,
					   const char *pattern,
					   const char *pattern_end)
{
	const char *pattern_start = pattern;
	bool first = true;
	bool result;

	while (pattern < pattern_end - 1) {
		/* Split at "\-" pattern. */
		if (*pattern++ != '\\' || *pattern++ != '-')
			continue;
		result = tomoyo_file_matches_to_pattern2(filename,
							 filename_end,
							 pattern_start,
							 pattern - 2);
		if (first)
			result = !result;
		if (result)
			return false;
		first = false;
		pattern_start = pattern;
	}
	result = tomoyo_file_matches_to_pattern2(filename, filename_end,
						 pattern_start, pattern_end);
	return first ? result : !result;
}